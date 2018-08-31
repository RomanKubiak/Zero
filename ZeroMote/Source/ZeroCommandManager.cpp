/*
  ==============================================================================

    ZeroCommands.cpp
    Created: 31 May 2018 5:42:30pm
    Author:  atom

  ==============================================================================
*/

#include "ZeroCommandManager.h"

ZeroCommandManager::ZeroCommandManager()
	: writeBuffer(nullptr), writeBufferSize(0), 
	connectedToRobot(false), Thread("network thread"),
	areWeInControl(false)
{
	writeBuffer = (char *)malloc(8192);
	socket = new StreamingSocket();
	
	File f("c:\\devel\\Zero\\ZeroMote\\keymap.json");
	var keymapfile;
	Result ret = JSON::parse (f.loadFileAsString(), keymapfile);

	if (!ret.wasOk())
	{
		AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Keymap parser", "Can't parse json: " + ret.getErrorMessage());
	}
	else
	{
		keymap = keymapfile.getProperty("keymap", var::null);
	}
	
}

ZeroCommandManager::~ZeroCommandManager()
{
	stopThread(1500);
	socket->close();
	free(writeBuffer);
}

void ZeroCommandManager::setCameraPan(int16_t angle, bool is_relative)
{
	if (!connectedToRobot) return;
	char buf[128];
	sprintf(buf, "%s:%d:0=%d\r", CMD_SERVO, is_relative, angle);
	socket->write(buf, strlen(buf));
}
void ZeroCommandManager::setCameraTilt(int16_t angle, bool is_relative)
{
	if (!connectedToRobot) return;
	char buf[128];
	sprintf(buf, "%s:%d:1=%d\r", CMD_SERVO, is_relative, angle);
	socket->write(buf, strlen(buf));
}

void ZeroCommandManager::requestI2CScan()
{
	if (!connectedToRobot) return;
	socket->write(CMD_I2CSCAN, 3);
}

void ZeroCommandManager::requestHealth()
{
	if (!connectedToRobot) return;
	socket->write(CMD_READ, 2);
}

void ZeroCommandManager::setMotors(int16_t left, int16_t right)
{
	if (!connectedToRobot) return;
	char buf[16];
	sprintf(buf, "%s:%d:%d\r", CMD_MOTO, left, right);
	_DBG(buf);
	socket->write(buf, strlen(buf));
}

void ZeroCommandManager::setControlling(const bool _areWeInControl)
{
	areWeInControl = _areWeInControl;

	for (int k = 0; k < listeners.size(); k++)
	{
		listeners.getListeners()[k]->controlChanged(_areWeInControl);
	}
}

bool ZeroCommandManager::connectToRobot(const RemoteRobotItem &_currentRobot)
{
	currentRobot = _currentRobot;
	connectedToRobot = false;

	if (socket)
	{
		if (socket->isConnected())
		{
			socket->close();
		}

		connectedToRobot = socket->connect(
			currentRobot.controlUrl.getDomain(),
			currentRobot.controlUrl.getPort(),
			1000
		);

		if (connectedToRobot)
		{
			_DBG("Connected to: " + currentRobot.controlUrl.toString(true));
			startThread();
		}
		else
		{
			_ERR("Can't connect to: " + currentRobot.controlUrl.toString(true));
		}
	}
	else
	{
		_ERR("no socket created");
		stopThread(1500);
	}

	for (int i = 0; i < listeners.size(); i++)
	{
		listeners.getListeners()[i]->connectedToRobot();
	}

	return (connectedToRobot);
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

void ZeroCommandManager::handleAsyncUpdate()
{
	{
		ScopedLock sl(readData.getLock());
		for (int i = 0; i < readData.size(); i++)
		{
			for (int k = 0; k < listeners.size(); k++)
			{
				listeners.getListeners()[k]->liveDataUpdated(readData[i]);
			}
		}
		readData.clear();
	}
}

void ZeroCommandManager::run()
{
	while (!threadShouldExit())
	{
		if (socket != nullptr)
		{
			const int ready = socket->waitUntilReady (true, 0);

			if (ready < 0)
			{
				break;
			}

			if (ready == 0)
			{
				wait (1);
				continue;
			}
		}
		else
		{
			break;
		}

		if (threadShouldExit() || !readNextMessageInt())
			break;
	}
}

bool ZeroCommandManager::readNextMessageInt()
{
	uint8_t messageHeader[10];
	const int bytes = socket->read (messageHeader, sizeof (messageHeader), true);

	if (bytes == sizeof (messageHeader)
		&& messageHeader[0] == '\r'
		&& messageHeader[1] == '\n')
	{
		int bytesInMessage = strtol((const char *)&messageHeader[2], NULL, 16);

		if (bytesInMessage > 0)
		{
			MemoryBlock messageData ((size_t)bytesInMessage, true);
			int bytesRead = 0;

			while (bytesInMessage > 0)
			{
				if (threadShouldExit())
					return false;

				const int numThisTime = jmin (bytesInMessage, 65536);
				void* const data = addBytesToPointer (messageData.getData(), bytesRead);

				const int bytesIn = socket->read (data, numThisTime, true);

				if (bytesIn <= 0)
					break;

				bytesRead += bytesIn;
				bytesInMessage -= bytesIn;
			}

			if (bytesRead >= 0)
			{
				ScopedLock sl(readData.getLock());
				readData.add(messageData);
				triggerAsyncUpdate();
			}
		}

	}

	else if (bytes < 0)
	{
		return false;
	}
	return (true);
}