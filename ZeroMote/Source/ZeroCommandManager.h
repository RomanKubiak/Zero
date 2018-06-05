/*
  ==============================================================================

    ZeroCommands.h
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#pragma once
#include <mpack/mpack.h>
#include <../shared/config.h>
#include "../JuceLibraryCode/JuceHeader.h"

#define _DBG(s, ...) Logger::writeToLog(String::formatted(s, __VA_ARGS__))

class ZeroCommandManager
{
	public:
		ZeroCommandManager();
		~ZeroCommandManager();
		void setCameraPan(uint8_t angle);
		void setCameraTilt(uint8_t angle);

	private:
		void writeAuthCode();
		char *writeBuffer;
		size_t writeBufferSize;
		mpack_writer_t writer;
		ScopedPointer<DatagramSocket> udpSocket;
};