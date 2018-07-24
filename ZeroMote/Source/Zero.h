/*
  ==============================================================================

    Zero.h
    Created: 31 May 2018 6:02:46pm
    Author:  atom

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct RemoteRobotItem
{
	RemoteRobotItem() : name(String::empty) {}
	RemoteRobotItem(const String &_name, const URL &_url) : name(_name), url(_url) {}
	String name;
	URL url;
};

#define _DBG(s, ...) Logger::writeToLog(String::formatted(String("DBG") + String(s), __VA_ARGS__))
#define _ERR(s, ...) Logger::writeToLog(String::formatted(String("ERR") + String(s), __VA_ARGS__))