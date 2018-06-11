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
#include "Zero.h"

class ZeroCommandManager
{
	public:
		ZeroCommandManager();
		~ZeroCommandManager();
		void setCameraPan(uint8_t angle);
		void setCameraTilt(uint8_t angle);

		void setNeuralHost(const String &_neuralHost) { neuralHost = _neuralHost;  }
		void setNeuralPort(const int &_neuralPort) { neuralPort = _neuralPort;  }
		void requestI2CScan();
		void requestHealth();
		void setRemoteMode();
		void setLocalMode();
	private:
		void writeAuthCode();
		char *writeBuffer;
		size_t writeBufferSize;
		mpack_writer_t writer;
		ScopedPointer<DatagramSocket> udpSocket;
		int neuralPort;
		String neuralHost;
};