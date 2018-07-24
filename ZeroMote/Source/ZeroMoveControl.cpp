/*
  ==============================================================================

    ZeroMoveControl.cpp
    Created: 24 Jul 2018 4:42:32pm
    Author:  rkubiak

  ==============================================================================
*/

#include "ZeroMoveControl.h"

ZeroMoveControl::ZeroMoveControl(ZeroCommandManager *_zeroCommandManager)
	: zeroCommandManager(_zeroCommandManager)
{

}

void ZeroMoveControl::timerCallback()
{
	sendChangeMessage();
}

void ZeroMoveControl::keyPressed(const KeyPress &key)
{
}

void ZeroMoveControl::keyStateChanged()
{
}