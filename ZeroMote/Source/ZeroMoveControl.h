/*
  ==============================================================================

    ZeroMoveControl.h
    Created: 24 Jul 2018 4:42:32pm
    Author:  rkubiak

  ==============================================================================
*/

#pragma once
#include "Zero.h"
class ZeroCommandManager;
class ZeroMoveControl : public Timer, public ChangeBroadcaster
{
	public:
		ZeroMoveControl(ZeroCommandManager *_zeroCommandManager);
		void timerCallback();
		void keyPressed(const KeyPress &key);
		void keyStateChanged();
		BigInteger flags;

	private:
		ZeroCommandManager *zeroCommandManager;
};