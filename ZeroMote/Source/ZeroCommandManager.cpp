/*
  ==============================================================================

    ZeroCommands.cpp
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#include "ZeroCommandManager.h"

ZeroCommandManager::ZeroCommandManager()
	: writeBuffer(nullptr), writeBufferSize(0), isActive(false), Thread("network thread")
{
	writeBuffer = (char *)malloc(CONFIG_MPACK_WRITER_BUFFER);
	udpSocket = new DatagramSocket(false);
	udpSocket->bindToPort(0);

	if (!JSON::parse(String(BinaryData::keymap_json, BinaryData::keymap_jsonSize), keymap).wasOk())
	{
		Logger::writeToLog("can't parse keymap");
	}
	startThread();
}

ZeroCommandManager::~ZeroCommandManager()
{
	free(writeBuffer);
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
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
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
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::requestI2CScan()
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_I2C_SCAN);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
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
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::setRemoteMode()
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_MODE_REMOTE);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::setLocalMode()
{
	if (!isActive) return;
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_MODE_LOCAL);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
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
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
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

void ZeroCommandManager::run()
{
	MemoryBlock readBuffer(1024);
	while (int ret = udpSocket->waitUntilReady(true, 500))
	{
		if (ret == -1)
		{
			_ERR("udp socket error");
			return;
		}

		if (threadShouldExit())
		{
			_DBG("network thread exiting");
			return;
		}

		if (ret == 1)
		{
			_DBG("socket ready for reading");
			const int readSize = udpSocket->read(readBuffer.getData(), readBuffer.getSize(), true);
			if (readSize > 0)
			{
				_DBG("got %d bytes of data", readSize);
			}
		}
	}
}