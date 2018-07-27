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

#include "ZeroLiveStatus.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "ZeroCommandManager.h"
//[/MiscUserDefs]

//==============================================================================
ZeroLiveStatus::ZeroLiveStatus (ZeroCommandManager *_zeroCommandManager)
    : zeroCommandManager(_zeroCommandManager)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("AZMT: 000\n"
                                          "SPDL: 000\n"
                                          "SPDR: 000\n"
                                          "CAMP: 000\n"
                                          "CAMT: 000\n"
                                          "CURR: 000")));
    label->setFont (Font ("Terminus (TTF)", 16.00f, Font::bold).withExtraKerningFactor (0.090f));
    label->setJustificationType (Justification::centredTop);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (128, 100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ZeroLiveStatus::~ZeroLiveStatus()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroLiveStatus::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x66000000));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroLiveStatus::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ZeroLiveStatus::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
	if (isVisible())
	{
		startTimerHz(10);
	}
	else
	{
		stopTimer();
	}
    //[/UserCode_visibilityChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroLiveStatus::timerCallback()
{
	zeroCommandManager->requestHealth();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroLiveStatus" componentName=""
                 parentClasses="public Component, public Timer" constructorParams="ZeroCommandManager *_zeroCommandManager"
                 variableInitialisers="zeroCommandManager(_zeroCommandManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="128" initialHeight="100">
  <METHODS>
    <METHOD name="visibilityChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="66000000"/>
  <LABEL name="new label" id="1089af106cfca5eb" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 0M 0M" edTextCol="ff000000" edBkgCol="0"
         labelText="AZMT: 000&#10;SPDL: 000&#10;SPDR: 000&#10;CAMP: 000&#10;CAMT: 000&#10;CURR: 000"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Terminus (TTF)" fontsize="16" kerning="0.089999999999999996669"
         bold="1" italic="0" justification="12" typefaceStyle="Bold"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
