/*
  ==============================================================================

    ZeroCommands.cpp
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#include "ZeroCommandManager.h"

ZeroCommandManager::ZeroCommandManager() 
	: writeBuffer(nullptr), writeBufferSize(0)
{
	writeBuffer = (char *)malloc(CONFIG_MPACK_WRITER_BUFFER);
	udpSocket = new DatagramSocket(false);
}

ZeroCommandManager::~ZeroCommandManager()
{
	free(writeBuffer);
}

void ZeroCommandManager::setCameraPan(uint8_t angle)
{
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 4);
	mpack_write_u8(&writer, MSG_CMD);
	mpack_write_u8(&writer, CMD_SERVO);
	mpack_write_u8(&writer, (uint8_t)servo_pan);
	mpack_write_u8(&writer, angle);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}
void ZeroCommandManager::setCameraTilt(uint8_t angle)
{
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 4);
	mpack_write_u8(&writer, MSG_CMD);
	mpack_write_u8(&writer, CMD_SERVO);
	mpack_write_u8(&writer, (uint8_t)servo_tilt);
	mpack_write_u8(&writer, angle);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::requestI2CScan()
{
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
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_HEALTH_UPDATE);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::setRemoteMode()
{
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_MODE_REMOTE);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}

void ZeroCommandManager::setLocalMode()
{
	mpack_writer_init_growable(&writer, &writeBuffer, &writeBufferSize);
	writeAuthCode();
	mpack_start_array(&writer, 1);
	mpack_write_u8(&writer, MSG_MODE_LOCAL);
	mpack_writer_destroy(&writer);
	udpSocket->write(neuralHost, neuralPort, (void *)writeBuffer, writeBufferSize);
}