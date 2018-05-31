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

    addAndMakeVisible (bottomState = new Label ("bottom",
                                                TRANS("--:--:--")));
    bottomState->setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bottomState->setJustificationType (Justification::centred);
    bottomState->setEditable (false, false, false);
    bottomState->setColour (TextEditor::textColourId, Colours::black);
    bottomState->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (camPan = new Slider ("Camera Pan"));
    camPan->setRange (0, 180, 1);
    camPan->setSliderStyle (Slider::LinearHorizontal);
    camPan->setTextBoxStyle (Slider::TextBoxRight, true, 32, 20);
    camPan->setColour (Slider::backgroundColourId, Colours::white);
    camPan->setColour (Slider::thumbColourId, Colour (0xbeff0ea6));
    camPan->setColour (Slider::trackColourId, Colours::black);
    camPan->setColour (Slider::rotarySliderOutlineColourId, Colour (0x84ffffff));
    camPan->addListener (this);

    addAndMakeVisible (camTilt = new Slider ("Camera Tilt"));
    camTilt->setRange (0, 180, 1);
    camTilt->setSliderStyle (Slider::LinearVertical);
    camTilt->setTextBoxStyle (Slider::TextBoxBelow, true, 80, 20);
    camTilt->setColour (Slider::backgroundColourId, Colours::white);
    camTilt->setColour (Slider::thumbColourId, Colour (0xbeff0ea6));
    camTilt->setColour (Slider::trackColourId, Colours::black);
    camTilt->setColour (Slider::rotarySliderOutlineColourId, Colour (0x84ffffff));
    camTilt->addListener (this);


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

    bottomState = nullptr;
    camPan = nullptr;
    camTilt = nullptr;


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

    bottomState->setBounds (0, getHeight() - 24, proportionOfWidth (1.0000f), 24);
    camPan->setBounds (0, getHeight() - 64, getWidth() - 0, 32);
    camTilt->setBounds (getWidth() - 32, 0, 32, getHeight() - 64);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ZeroVideoOverlay::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == camPan)
    {
        //[UserSliderCode_camPan] -- add your slider handling code here..
		zeroCommandManager->setCameraPan(camPan->getValue());
        //[/UserSliderCode_camPan]
    }
    else if (sliderThatWasMoved == camTilt)
    {
        //[UserSliderCode_camTilt] -- add your slider handling code here..
		zeroCommandManager->setCameraTilt(camTilt->getValue());
        //[/UserSliderCode_camTilt]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroVideoOverlay::vlcTimeChanged(int64_t newTime)
{
	MessageManagerLock mmlock;
	bottomState->setText(String(newTime),sendNotificationAsync);
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
  <LABEL name="bottom" id="436cf21e24ae3409" memberName="bottomState"
         virtualName="" explicitFocusOrder="0" pos="0 24R 100% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="--:--:--" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="36"/>
  <SLIDER name="Camera Pan" id="f10b34363fa15f96" memberName="camPan" virtualName=""
          explicitFocusOrder="0" pos="0 64R 0M 32" bkgcol="ffffffff" thumbcol="beff0ea6"
          trackcol="ff000000" rotaryslideroutline="84ffffff" min="0" max="180"
          int="1" style="LinearHorizontal" textBoxPos="TextBoxRight" textBoxEditable="0"
          textBoxWidth="32" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <SLIDER name="Camera Tilt" id="fa05d55fdde35b26" memberName="camTilt"
          virtualName="" explicitFocusOrder="0" pos="32R 0 32 64M" bkgcol="ffffffff"
          thumbcol="beff0ea6" trackcol="ff000000" rotaryslideroutline="84ffffff"
          min="0" max="180" int="1" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
