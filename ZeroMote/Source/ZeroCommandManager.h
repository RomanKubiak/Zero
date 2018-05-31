/*
  ==============================================================================

    ZeroCommands.h
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#pragma once
#include <mpack/mpack.h>
#include "../JuceLibraryCode/JuceHeader.h"

/* MSGPACK commands */
#define MSG_HEARTBEAT 	0xe1
#define MSG_STATUS	0xe2
#define MSG_CMD		0xe3
#define MSG_PONG	0xe4
#define MSG_PING	0xe5
#define MSG_UNKNOWN	0xef
#define MSG_ACK_CMD	0xe6
#define MSG_NAK_CMD	0xe7

#define CMD_MOTOR	0xf1
#define CMD_SERVO	0xf2
#define CMD_RADAR	0xf3
#define CMD_NEOPIXEL	0xf4
#define CMD_RESET	0xf5

enum servo_function
{
	servo_pan,
	servo_tilt,
	servo_radar,
	servo_count
};

#define _DBG(s, ...) Logger::writeToLog(String::formatted(s, __VA_ARGS__))

class ZeroCommandManager
{
	public:
		ZeroCommandManager();
		~ZeroCommandManager();
		void setCameraPan(uint8_t angle);
		void setCameraTilt(uint8_t angle);

	private:
		char *writeBuffer;
		size_t writeBufferSize;
		mpack_writer_t writer;
		ScopedPointer<DatagramSocket> udpSocket;
};