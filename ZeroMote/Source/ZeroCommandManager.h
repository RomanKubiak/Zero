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

class ZeroCommandManager : public Thread
{
	public:
		ZeroCommandManager();
		~ZeroCommandManager();
		void setCameraPan(int16_t angle, bool is_relative=false);
		void setCameraTilt(int16_t angle, bool is_relative=false);
		void run();
		void setNeuralHost(const String &_neuralHost) { neuralHost = _neuralHost;  }
		void setNeuralPort(const int &_neuralPort) { neuralPort = _neuralPort;  }
		void requestI2CScan();
		void requestHealth();
		void setRemoteMode();
		void setLocalMode();
		void setActive(bool _isActive) { isActive = _isActive;  }
		void setMotors(int16_t left, int16_t right);

		void connectToRobot(const RemoteRobotItem &robot);
		class Listener
		{
			public:
				virtual void connectToRobot(const RemoteRobotItem &robot) {}
		};
		void addListener(ZeroCommandManager::Listener *listenerToAdd) { listeners.add(listenerToAdd); }
		String getCodeForAction(const Identifier &actionId);
	private:
		bool isActive;
		void writeAuthCode();
		char *writeBuffer;
		size_t writeBufferSize;
		mpack_writer_t writer;
		ScopedPointer<DatagramSocket> udpSocket;
		int neuralPort;
		String neuralHost;
		ListenerList <Listener> listeners;
		var keymap;
};