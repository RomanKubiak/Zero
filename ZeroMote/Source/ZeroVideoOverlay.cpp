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
ZeroVideoOverlay::ZeroVideoOverlay ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (cameraControl = new ZeroXYComponent());

    //[UserPreSize]
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

    cameraControl = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroVideoOverlay::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
	if (hasKeyboardFocus(true))
	{
		g.setColour(Colours::white);
		g.drawText("Sendind...", 0, 0, 64, 16, Justification::centred);
	}
	else
	{
		g.setColour(Colours::white);
		g.drawText("Viewing...", 0, 0, 64, 16, Justification::centred);
	}
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroVideoOverlay::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    cameraControl->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

bool ZeroVideoOverlay::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
	_DBG("ZeroVideoOverlay::keyPressed\n");
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}

bool ZeroVideoOverlay::keyStateChanged (bool isKeyDown)
{
    //[UserCode_keyStateChanged] -- Add your code here...
	_DBG("ZeroVideoOverlay::keyStateChanged\n");
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyStateChanged]
}

void ZeroVideoOverlay::modifierKeysChanged (const ModifierKeys& modifiers)
{
    //[UserCode_modifierKeysChanged] -- Add your code here...
	_DBG("ZeroVideoOverlay::modifierKeysChanged\n");
    //[/UserCode_modifierKeysChanged]
}

void ZeroVideoOverlay::focusGained (FocusChangeType cause)
{
    //[UserCode_focusGained] -- Add your code here...
	_DBG("ZeroVideoOverlay::focusGained\n");
    //[/UserCode_focusGained]
}

void ZeroVideoOverlay::focusLost (FocusChangeType cause)
{
    //[UserCode_focusLost] -- Add your code here...
	_DBG("ZeroVideoOverlay::focusLost\n");
    //[/UserCode_focusLost]
}

void ZeroVideoOverlay::focusOfChildComponentChanged (FocusChangeType cause)
{
    //[UserCode_focusOfChildComponentChanged] -- Add your code here...
	_DBG("ZeroVideoOverlay::focusOfChildComponentChanged\n");
    //[/UserCode_focusOfChildComponentChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroVideoOverlay::vlcTimeChanged(int64_t newTime)
{
}

void ZeroVideoOverlay::vlcPaused()
{

}
void ZeroVideoOverlay::vlcStarted()
{

}
void ZeroVideoOverlay::vlcStopped()
{

}

void ZeroVideoOverlay::setCommandManager(ZeroCommandManager *_zeroCommandManager)
{
	zeroCommandManager = _zeroCommandManager;
	cameraControl->setCommandManager(_zeroCommandManager);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroVideoOverlay" componentName=""
                 parentClasses="public Component, public VLCEventCallback" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="320" initialHeight="200">
  <METHODS>
    <METHOD name="keyStateChanged (bool isKeyDown)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
    <METHOD name="modifierKeysChanged (const ModifierKeys&amp; modifiers)"/>
    <METHOD name="focusGained (FocusChangeType cause)"/>
    <METHOD name="focusLost (FocusChangeType cause)"/>
    <METHOD name="focusOfChildComponentChanged (FocusChangeType cause)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <JUCERCOMP name="" id="bd64555f2b9faa51" memberName="cameraControl" virtualName=""
             explicitFocusOrder="0" pos="0 0 0M 0M" sourceFile="ZeroXYComponent.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
