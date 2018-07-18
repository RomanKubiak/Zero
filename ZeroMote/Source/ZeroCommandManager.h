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
		void setCameraPan(int16_t angle, bool is_relative=false);
		void setCameraTilt(int16_t angle, bool is_relative=false);

		void setNeuralHost(const String &_neuralHost) { neuralHost = _neuralHost;  }
		void setNeuralPort(const int &_neuralPort) { neuralPort = _neuralPort;  }
		void requestI2CScan();
		void requestHealth();
		void setRemoteMode();
		void setLocalMode();
		void setActive(bool _isActive) { isActive = _isActive;  }
		void setMotors(int16_t left, int16_t right);
	private:
		bool isActive;
		void writeAuthCode();
		char *writeBuffer;
		size_t writeBufferSize;
		mpack_writer_t writer;
		ScopedPointer<DatagramSocket> udpSocket;
		int neuralPort;
		String neuralHost;
};