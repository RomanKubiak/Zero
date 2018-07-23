/*
  ==============================================================================

    Zero.h
    Created: 31 May 2018 6:02:46pm
    Author:  atom

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define ZEROMOTE_KEY_CONSOLE	96
#define ZEROMOTE_KEY_STATUS		9
#define ZEROMOTE_KEY_LIVE		65648
#define ZEROMOTE_KEY_FORWARD	87
#define ZEROMOTE_KEY_BACKWARD	83
#define ZEROMOTE_KEY_RIGHT		68
#define ZEROMOTE_KEY_LEFT		65
#define ZEROMOTE_SPEED_CHANGE	ModifierKeys::Flags::shiftModifier

enum MovingSpeed
{
	stopped,
	crawl,
	walk,
	pace,
	run,
	crazy
};

enum PanningSpeed
{
	slow,
	normal,
	faster,
	berserk
};

struct RemoteRobotItem
{
	RemoteRobotItem() : name(String::empty) {}
	RemoteRobotItem(const String &_name, const URL &_url) : name(_name), url(_url) {}
	String name;
	URL url;
};

#define _DBG(s, ...) Logger::writeToLog(String::formatted(String("DBG") + String(s), __VA_ARGS__))
#define _ERR(s, ...) Logger::writeToLog(String::formatted(String("ERR") + String(s), __VA_ARGS__))