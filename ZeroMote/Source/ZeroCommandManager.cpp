/*
  ==============================================================================

    ZeroCommands.cpp
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#include "ZeroCommandManager.h"

ZeroCommandManager::ZeroCommandManager()
	: writeBuffer(nullptr), writeBufferSize(0), 
	is_connected(false), isActive(false), Thread("network thread")
{
	writeBuffer = (char *)malloc(CONFIG_MPACK_WRITER_BUFFER);
	netSocket = new StreamingSocket();
	netSocket->bindToPort(0);
	File f("c:\\devel\\Zero\\ZeroMote\\keymap.json");
	var keymapfile;
	Result ret = JSON::parse (f.loadFileAsString(), keymapfile);

	if (!ret.wasOk())
	{
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Keymap parser", "Can't parse json: " + ret.getErrorMessage());
	}
	else
	{
		keymap = keymapfile.getProperty("keymap", var::null);
	}
	
}

ZeroCommandManager::~ZeroCommandManager()
{
	stopThread(1500);
	netSocket->close();
	free(writeBuffer);
}

bool ZeroCommandManager::setActive(bool _isActive)
{
	isActive = _isActive;
	_DBG("ZeroCommandManager::setActive");
	if (netSocket)
	{
		if (netSocket->isConnected())
		{
			netSocket->close();
		}
		
		is_connected = netSocket->connect(neuralHost, neuralPort, 1000);
		if (is_connected)
			startThread();
		
		return (is_connected);
	}
	else
	{
		_ERR("no socket created");
		stopThread(1500);
		return (false);
	}
}

void ZeroCommandManager::setCameraPan(int16_t angle, bool is_relative)
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 4);
	mpack_write_u8(&writer, MSG_CMD);
	mpack_write_u8(&writer, CMD_SERVO);
	mpack_write_u8(&writer, (uint8_t)servo_pan);
	mpack_write_i16(&writer, angle);
	mpack_write_bool(&writer, is_relative);
	mpack_writer_destroy(&writer);
	netSocket->write((void *)writeBuffer, writeBufferSize);
}
void ZeroCommandManager::setCameraTilt(int16_t angle, bool is_relative)
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 4);
	mpack_write_u8(&writer, MSG_CMD);
	mpack_write_u8(&writer, CMD_SERVO);
	mpack_write_u8(&writer, (uint8_t)servo_tilt);
	mpack_write_i16(&writer, angle);
	mpack_write_bool(&writer, is_relative);
	mpack_writer_destroy(&writer);
	netSocket->write((void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::requestI2CScan()
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_I2C_SCAN);
	mpack_writer_destroy(&writer);
	int w = netSocket->write((void *)writeBuffer, writeBufferSize);
	_DBG("writtren %d bytes to socket", w);
}

void ZeroCommandManager::writeAuthCode()
{
	mpack_start_array(&writer, 2);
	mpack_write_u8(&writer, CONFIG_AUTH_TOKEN_TYPE);
	mpack_write_u32(&writer, CONFIG_AUTH_TOKEN);
}

void ZeroCommandManager::requestHealth()
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_HEALTH_UPDATE);
	mpack_writer_destroy(&writer);
	netSocket->write((void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::setRemoteMode()
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_MODE_REMOTE);
	mpack_writer_destroy(&writer);
	netSocket->write((void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::setLocalMode()
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_MODE_LOCAL);
	mpack_writer_destroy(&writer);
	netSocket->write((void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::setMotors(int16_t left, int16_t right)
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 4);
	mpack_write_u8(&writer, MSG_CMD);
	mpack_write_u8(&writer, CMD_MOTOR);
	mpack_write_i16(&writer, (int16_t)left);
	mpack_write_i16(&writer, (int16_t)right);
	mpack_writer_destroy(&writer);
	netSocket->write((void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::connectToRobot(const RemoteRobotItem &robot)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners.getListeners()[i]->connectToRobot(robot);
	}
}

String ZeroCommandManager::getCodeForAction(const Identifier &actionId)
{
	DynamicObject *o = keymap.getDynamicObject();
	if (o)
	{
		var action = o->getProperty(actionId);
		if (action.getDynamicObject())
		{
			return (action.getDynamicObject()->getProperty("code"));
		}
	}
	return (String::empty);
}

void ZeroCommandManager::updateLiveData(mpack_reader_t *reader)
{
	current_status.current_draw = mpack_expect_uint(reader);
	current_status.azimuth_body = mpack_expect_uint(reader);
	current_status.battery_mv   = mpack_expect_uint(reader);
}

void ZeroCommandManager::handleAsyncUpdate()
{
	mpack_reader_t reader;
	ScopedLock sl(mpackData.getLock());
	const int size = mpackData.size();
	for (int i = 0; i < size; i++)
	{
		MemoryBlock bl = mpackData[i];
		mpack_reader_init_data(&reader, (const char *)bl.getData(), bl.getSize());
		if (mpack_expect_array(&reader) > 0)
		{
			updateLiveData(&reader);
		}
	}
	mpackData.clear();

	for (int i = 0; i < listeners.size(); i++)
	{
		listeners.getListeners()[i]->liveDataUpdated();
	}
}

void ZeroCommandManager::run()
{
	while (true)
	{
		int ret = netSocket->waitUntilReady(true, 500);
		if (ret == -1)
		{
			return;
		}

		if (threadShouldExit())
		{
			return;
		}

		if (ret == 1)
		{
			MemoryBlock readBuffer(512);
			const int readSize = netSocket->read(readBuffer.getData(), readBuffer.getSize(), false);
			readBuffer.setSize(readSize, false);
			ScopedLock sl(mpackData.getLock());
			mpackData.add(readBuffer);
			triggerAsyncUpdate();
		}
	}
}