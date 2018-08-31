/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ZeroMovingStatus.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "ZeroCommandManager.h"
//[/MiscUserDefs]

//==============================================================================
ZeroMovingStatus::ZeroMovingStatus (ZeroCommandManager *_zeroCommandManager)
    : zeroCommandManager(_zeroCommandManager)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
	up = down = left = right = false;
	upChanged = downChanged = leftChanged = rightChanged = false;
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
	startTimerHz(3);
    //[/Constructor]
}

ZeroMovingStatus::~ZeroMovingStatus()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroMovingStatus::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	Colour off = Colour (0x50ffffff);
	Colour on = Colours::white;
    //[/UserPrePaint]

    {
        float x = 0, y = 0;
        Colour fillColour = Colour (0x80ffffff);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		fillColour = up ? on : off;
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath1, AffineTransform::translation(x, y));
        g.setColour (strokeColour);
        g.strokePath (internalPath1, PathStrokeType (1.000f), AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        Colour fillColour = Colour (0x80ffffff);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		fillColour = right ? on : off;
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath2, AffineTransform::translation(x, y));
        g.setColour (strokeColour);
        g.strokePath (internalPath2, PathStrokeType (1.000f), AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        Colour fillColour = Colour (0x80ffffff);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		fillColour = down ? on : off;
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath3, AffineTransform::translation(x, y));
        g.setColour (strokeColour);
        g.strokePath (internalPath3, PathStrokeType (1.000f), AffineTransform::translation(x, y));
    }

    {
        float x = 0, y = 0;
        Colour fillColour = Colour (0x80ffffff);
        Colour strokeColour = Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
    		fillColour = left ? on : off;
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillPath (internalPath4, AffineTransform::translation(x, y));
        g.setColour (strokeColour);
        g.strokePath (internalPath4, PathStrokeType (1.000f), AffineTransform::translation(x, y));
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroMovingStatus::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    internalPath1.clear();
    internalPath1.startNewSubPath (static_cast<float> ((getWidth() / 2)), 0.0f);
    internalPath1.lineTo (static_cast<float> (proportionOfWidth (0.7000f)), static_cast<float> (proportionOfHeight (0.3000f)));
    internalPath1.lineTo (static_cast<float> (proportionOfWidth (0.3000f)), static_cast<float> (proportionOfHeight (0.3000f)));
    internalPath1.closeSubPath();

    internalPath2.clear();
    internalPath2.startNewSubPath (static_cast<float> (proportionOfWidth (0.7000f)), static_cast<float> (proportionOfHeight (0.3000f)));
    internalPath2.lineTo (static_cast<float> (getWidth()), static_cast<float> (proportionOfHeight (0.5000f)));
    internalPath2.lineTo (static_cast<float> (proportionOfWidth (0.7000f)), static_cast<float> (proportionOfHeight (0.7000f)));
    internalPath2.closeSubPath();

    internalPath3.clear();
    internalPath3.startNewSubPath (static_cast<float> (proportionOfWidth (0.5000f)), static_cast<float> (getHeight()));
    internalPath3.lineTo (static_cast<float> (proportionOfWidth (0.7000f)), static_cast<float> (proportionOfHeight (0.7000f)));
    internalPath3.lineTo (static_cast<float> (proportionOfWidth (0.3000f)), static_cast<float> (proportionOfHeight (0.7000f)));
    internalPath3.closeSubPath();

    internalPath4.clear();
    internalPath4.startNewSubPath (static_cast<float> (proportionOfWidth (0.3000f)), static_cast<float> (proportionOfHeight (0.3000f)));
    internalPath4.lineTo (static_cast<float> (proportionOfWidth (0.3000f)), static_cast<float> (proportionOfHeight (0.7000f)));
    internalPath4.lineTo (0.0f, static_cast<float> (proportionOfHeight (0.5000f)));
    internalPath4.closeSubPath();

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroMovingStatus::setStatus(bool _up, bool _down, bool _left, bool _right, uint8_t _speed)
{
	upChanged		= (up != _up);
	downChanged		= (down != _down);
	leftChanged		= (left != _left);
	rightChanged	= (right != _right);

	up = _up;
	down = _down;
	left = _left;
	right = _right;
	speed = _speed;
}

void ZeroMovingStatus::changeListenerCallback(ChangeBroadcaster *b)
{
}

void ZeroMovingStatus::timerCallback()
{
	setStatus(
		KeyPress::isKeyCurrentlyDown(KeyPress::createFromDescription(zeroCommandManager->getCodeForAction("up")).getKeyCode()),
		KeyPress::isKeyCurrentlyDown(KeyPress::createFromDescription(zeroCommandManager->getCodeForAction("down")).getKeyCode()),
		KeyPress::isKeyCurrentlyDown(KeyPress::createFromDescription(zeroCommandManager->getCodeForAction("left")).getKeyCode()),
		KeyPress::isKeyCurrentlyDown(KeyPress::createFromDescription(zeroCommandManager->getCodeForAction("right")).getKeyCode())
	);
	const bool ctl = zeroCommandManager->getControlStatus();
	if (upChanged || leftChanged || downChanged || rightChanged)
	{
		_DBG("ctl: %d up:%d/%d down:%d/%d left:%d/%d right:%d/%d", ctl, up, upChanged, down, downChanged, left, leftChanged, right, rightChanged);
		if (ctl)
		{
			up ? zeroCommandManager->setMotors(32, 32) : zeroCommandManager->setMotors(0,0);
		}
	}
	//repaint();
}

bool ZeroMovingStatus::keyPressed (const KeyPress& key)
{
	//[UserCode_keyPressed] -- Add your code here...
	return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
				   //[/UserCode_keyPressed]
}

bool ZeroMovingStatus::keyStateChanged (bool isKeyDown)
{
	//[UserCode_keyStateChanged] -- Add your code here...
	return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
				   //[/UserCode_keyStateChanged]
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroMovingStatus" componentName=""
                 parentClasses="public Component, public ChangeListener, public Timer"
                 constructorParams="ZeroCommandManager *_zeroCommandManager" variableInitialisers="zeroCommandManager(_zeroCommandManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="0">
    <PATH pos="0 0 100 100" fill="solid: 80ffffff" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 0C 0 l 70% 30% l 30% 30% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: 80ffffff" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 70% 30% l 0R 50% l 70% 70% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: 80ffffff" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 50% 0R l 70% 70% l 30% 70% x</PATH>
    <PATH pos="0 0 100 100" fill="solid: 80ffffff" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ffffffff" nonZeroWinding="1">s 30% 30% l 30% 70% l 0 50% x</PATH>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
