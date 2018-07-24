/*
  ==============================================================================

    ZeroCommands.cpp
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#include "ZeroCommandManager.h"

ZeroCommandManager::ZeroCommandManager() 
	: writeBuffer(nullptr), writeBufferSize(0), isActive(false)
{
	writeBuffer = (char *)malloc(CONFIG_MPACK_WRITER_BUFFER);
	udpSocket = new DatagramSocket(false);

	if (!JSON::parse(String(BinaryData::keymap_json, BinaryData::keymap_jsonSize), keymap).wasOk())
	{
		Logger::writeToLog("can't parse keymap");
	}
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

bool ZeroCommandManager::isStatusToggle(const KeyPress &key)
{
	DynamicObject *o = keymap.getDynamicObject();
	if (o)
	{
		_DBG("top size: %d\n", o->getProperties().size());
		var live_status = o->getProperty("live_status");
		if (live_status.getDynamicObject())
		{
			_DBG("  live_status size: %d\n", live_status.getDynamicObject()->getProperties().size());
		}
	}
	return (false);
}

bool ZeroCommandManager::isLiveToggle(const KeyPress &key)
{
	return (false);
}

bool ZeroCommandManager::isConsoleToggle(const KeyPress &key)
{
	return (false);
}