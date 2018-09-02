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
#include "ZeroCommandManager.h"
//[/Headers]

#include "ZeroActionBar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ZeroActionBar::ZeroActionBar (ZeroCommandManager *_zeroCommandManager)
    : zeroCommandManager(_zeroCommandManager)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (act_i2c = new TextButton ("i2c"));
    act_i2c->setButtonText (TRANS("I2C Scan"));
    act_i2c->addListener (this);
    act_i2c->setColour (TextButton::buttonColourId, Colour (0xbe6ae7ff));
    act_i2c->setColour (TextButton::textColourOffId, Colour (0xff4b436f));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (256, 32);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ZeroActionBar::~ZeroActionBar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    act_i2c = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroActionBar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroActionBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    act_i2c->setBounds (0, 0, proportionOfWidth (0.3242f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ZeroActionBar::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == act_i2c)
    {
        //[UserButtonCode_act_i2c] -- add your button handler code here..
		zeroCommandManager->requestI2CScan();
        //[/UserButtonCode_act_i2c]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroActionBar" componentName=""
                 parentClasses="public Component" constructorParams="ZeroCommandManager *_zeroCommandManager"
                 variableInitialisers="zeroCommandManager(_zeroCommandManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="256" initialHeight="32">
  <BACKGROUND backgroundColour="0"/>
  <TEXTBUTTON name="i2c" id="537c5745da332883" memberName="act_i2c" virtualName=""
              explicitFocusOrder="0" pos="0 0 32.5% 100%" bgColOff="be6ae7ff"
              textCol="ff4b436f" buttonText="I2C Scan" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
