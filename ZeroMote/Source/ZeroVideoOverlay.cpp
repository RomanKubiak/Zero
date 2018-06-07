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
