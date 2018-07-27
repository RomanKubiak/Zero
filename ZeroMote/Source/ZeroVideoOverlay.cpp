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

#include "ZeroVideoOverlay.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "ZeroCommandManager.h"
//[/MiscUserDefs]

//==============================================================================
ZeroVideoOverlay::ZeroVideoOverlay (ZeroCommandManager *_zeroCommandManager)
    : zeroCommandManager(_zeroCommandManager)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (status = new ZeroStatus (zeroCommandManager));
    addAndMakeVisible (cameraControl = new ZeroXYComponent (zeroCommandManager));
    addAndMakeVisible (zeroConsole = new ZeroConsole());
    addAndMakeVisible (liveStatus = new ZeroLiveStatus (zeroCommandManager));
    addAndMakeVisible (movingStatus = new ZeroMovingStatus());

    //[UserPreSize]
	status->setVisible(false);
	//cameraControl->setVisible(false);
	liveStatus->setVisible(false);
	zeroMoveControl = new ZeroMoveControl(zeroCommandManager);
    //[/UserPreSize]

    setSize (320, 200);


    //[Constructor] You can add your own custom stuff here..
	cameraControl->setMouseClickGrabsKeyboardFocus(true);
    //[/Constructor]
}

ZeroVideoOverlay::~ZeroVideoOverlay()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    status = nullptr;
    cameraControl = nullptr;
    zeroConsole = nullptr;
    liveStatus = nullptr;
    movingStatus = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroVideoOverlay::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroVideoOverlay::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    status->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    cameraControl->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    zeroConsole->setBounds (0, 0, getWidth() - 0, proportionOfHeight (0.3000f));
    liveStatus->setBounds (getWidth() - 132, getHeight() - 100, 128, 94);
    movingStatus->setBounds (8, getHeight() - 108, 100, 100);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

bool ZeroVideoOverlay::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
	if (zeroCommandManager->getCodeForAction("console").equalsIgnoreCase(key.getTextDescription()))
	{
		if (zeroConsole->getY() == 0)
		{
			zeroConsole->setTopLeftPosition(0, -(zeroConsole->getHeight() * 0.8));
		}
		else
		{
			zeroConsole->setTopLeftPosition(0, 0);
		}
	}
	else if (zeroCommandManager->getCodeForAction("options").equalsIgnoreCase(key.getTextDescription()))
	{
		status->setVisible(!status->isVisible());
		if (status->isVisible())
			status->toFront(false);
	}
	else if (zeroCommandManager->getCodeForAction("live_status").equalsIgnoreCase(key.getTextDescription()))
	{
		liveStatus->setVisible(!liveStatus->isVisible());
	}
	else
	{
		zeroMoveControl->keyPressed(key);
	}
	return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}

bool ZeroVideoOverlay::keyStateChanged (bool isKeyDown)
{
    //[UserCode_keyStateChanged] -- Add your code here...
	zeroMoveControl->keyStateChanged();

    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyStateChanged]
}

void ZeroVideoOverlay::modifierKeysChanged (const ModifierKeys& modifiers)
{
    //[UserCode_modifierKeysChanged] -- Add your code here...
    //[/UserCode_modifierKeysChanged]
}

void ZeroVideoOverlay::focusGained (FocusChangeType cause)
{
    //[UserCode_focusGained] -- Add your code here...
    //[/UserCode_focusGained]
}

void ZeroVideoOverlay::focusLost (FocusChangeType cause)
{
    //[UserCode_focusLost] -- Add your code here...
    //[/UserCode_focusLost]
}

void ZeroVideoOverlay::focusOfChildComponentChanged (FocusChangeType cause)
{
    //[UserCode_focusOfChildComponentChanged] -- Add your code here...
    //[/UserCode_focusOfChildComponentChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroVideoOverlay::vlcTimeChanged(int64_t newTime)
{
}

void ZeroVideoOverlay::vlcPaused()
{
	zeroMoveControl->stopTimer();
}
void ZeroVideoOverlay::vlcStarted()
{
	zeroMoveControl->startTimerHz(15);
}
void ZeroVideoOverlay::vlcStopped()
{
	zeroMoveControl->stopTimer();
}

void ZeroVideoOverlay::changeListenerCallback(ChangeBroadcaster *b)
{
	if (b == zeroMoveControl.get())
		movingStatus->repaint();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroVideoOverlay" componentName=""
                 parentClasses="public Component, public VLCEventCallback, public ChangeListener"
                 constructorParams="ZeroCommandManager *_zeroCommandManager" variableInitialisers="zeroCommandManager(_zeroCommandManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="320" initialHeight="200">
  <METHODS>
    <METHOD name="keyStateChanged (bool isKeyDown)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
    <METHOD name="modifierKeysChanged (const ModifierKeys&amp; modifiers)"/>
    <METHOD name="focusGained (FocusChangeType cause)"/>
    <METHOD name="focusLost (FocusChangeType cause)"/>
    <METHOD name="focusOfChildComponentChanged (FocusChangeType cause)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <JUCERCOMP name="" id="78ea4c3b5cca81d0" memberName="status" virtualName=""
             explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="ZeroStatus.cpp"
             constructorParams="zeroCommandManager"/>
  <JUCERCOMP name="" id="bd64555f2b9faa51" memberName="cameraControl" virtualName=""
             explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="ZeroXYComponent.cpp"
             constructorParams="zeroCommandManager"/>
  <JUCERCOMP name="" id="440e44faebb5a133" memberName="zeroConsole" virtualName=""
             explicitFocusOrder="0" pos="0 0 0M 30%" sourceFile="ZeroConsole.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="25281c6779024c44" memberName="liveStatus" virtualName=""
             explicitFocusOrder="0" pos="132R 100R 128 94" sourceFile="ZeroLiveStatus.cpp"
             constructorParams="zeroCommandManager"/>
  <JUCERCOMP name="" id="32b80931dd9a5d8c" memberName="movingStatus" virtualName=""
             explicitFocusOrder="0" pos="8 108R 100 100" sourceFile="ZeroMovingStatus.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
