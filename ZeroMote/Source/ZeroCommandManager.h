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
		bool setActive(bool _isActive);
		void setMotors(int16_t left, int16_t right);
		void handleAsyncUpdate();
		void connectToRobot(const RemoteRobotItem &robot);
		class Listener
		{
			public:
				virtual void connectToRobot(const RemoteRobotItem &robot) {}
				virtual void liveDataUpdated() {}
		};
		void updateLiveData(mpack_reader_t *reader);
		void addListener(ZeroCommandManager::Listener *listenerToAdd) { listeners.add(listenerToAdd); }
		String getCodeForAction(const Identifier &actionId);
		current_status_t getLiveParameters() { return (current_status); }
	private:
		bool isActive;
		bool is_connected;
		void writeAuthCode();
		char *writeBuffer;
		size_t writeBufferSize;
		mpack_writer_t writer;
		ScopedPointer<StreamingSocket> netSocket;
		int neuralPort;
		String neuralHost;
		ListenerList <Listener> listeners;
		var keymap;
		Array<MemoryBlock, CriticalSection> mpackData;
		struct current_status_t current_status;
};