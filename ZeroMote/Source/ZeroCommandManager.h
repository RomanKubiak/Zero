/*
  ==============================================================================

    ZeroCommands.h
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Zero.h"

#define CMD_READ		"r\r"
#define CMD_I2CSCAN		">i\r"

struct current_status_t {};

class ZeroCommandManager : public Thread, public AsyncUpdater
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
		void setMotors(int16_t left, int16_t right);
		void handleAsyncUpdate();
		bool connectToRobot(const RemoteRobotItem &robot);
		RemoteRobotItem getCurrentRobot() { return currentRobot;  }
		class Listener
		{
			public:
				virtual void connectedToRobot() {}
				virtual void liveDataUpdated() {}
		};

		void addListener(ZeroCommandManager::Listener *listenerToAdd) { listeners.add(listenerToAdd); }
		void removeListener(ZeroCommandManager::Listener *listenerToRemove) { listeners.remove(listenerToRemove); }
		String getCodeForAction(const Identifier &actionId);
		current_status_t getLiveParameters() { return (current_status); }
		bool isConnected() { return connectedToRobot;  }
		bool readNextMessageInt();
	private:
		bool connectedToRobot;
		void writeAuthCode();
		char *writeBuffer;
		size_t writeBufferSize;
		ScopedPointer<StreamingSocket> socket;
		int neuralPort;
		String neuralHost;
		ListenerList <Listener> listeners;
		var keymap;
		Array<MemoryBlock, CriticalSection> readData;
		struct current_status_t current_status;
		RemoteRobotItem currentRobot;
};