/*
  ==============================================================================

    Zero.h
    Created: 31 May 2018 6:02:46pm
    Author:  atom

  ==============================================================================
*/

#pragma once
#define _DBG(s, ...) Logger::writeToLog(String::formatted(String("DBG") + String(s), __VA_ARGS__))
#define _ERR(s, ...) Logger::writeToLog(String::formatted(String("ERR") + String(s), __VA_ARGS__))