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

    addAndMakeVisible (list = new TableListBox ("params", this));
    list->setName ("params");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (128, 100);


    //[Constructor] You can add your own custom stuff here..
	list->getHeader().addColumn("name", 1, 32);
	list->getHeader().addColumn("value", 2, 32);
	list->setHeaderHeight(0);
	list->updateContent();
    //[/Constructor]
}

ZeroLiveStatus::~ZeroLiveStatus()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    list = nullptr;


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

    list->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
	list->getHeader().setColumnWidth(1, getWidth() / 2);
	list->getHeader().setColumnWidth(2, getWidth() / 2);
    //[/UserResized]
}

void ZeroLiveStatus::visibilityChanged()
{
    //[UserCode_visibilityChanged] -- Add your code here...
	if (isVisible())
	{
		startTimerHz(10);
		zeroCommandManager->addListener(this);
	}
	else
	{
		stopTimer();
		zeroCommandManager->removeListener(this);
	}
    //[/UserCode_visibilityChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroLiveStatus::timerCallback()
{
	zeroCommandManager->requestHealth();
}

void ZeroLiveStatus::liveDataUpdated(const MemoryBlock &data)
{
	/* az body
	   az camera
	   current
	   battery
	   servo0
	   servo1
	*/
	const String s = data.toString();
	const String sv = s.substring(0, 7);
	const uint32_t v = strtol(sv.toRawUTF8(), nullptr, 16);
	_DBG(sv);
}

int ZeroLiveStatus::getNumRows()
{
	return (params.getAllKeys().size());
}

void ZeroLiveStatus::paintCell (Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	const String &name	= params.getAllKeys()[rowNumber];
	const String &value = params.getAllValues()[rowNumber];
	g.setColour(Colours::white);
	g.setFont(height * 0.7f);
	
	if (columnId == 1)
		g.drawText(name, 0, 0, width, height, Justification::centredLeft);
	if (columnId == 2)
		g.drawText(value, 0, 0, width, height, Justification::centredLeft);
}

void ZeroLiveStatus::paintRowBackground (Graphics &g, int rowNumber, int width, int height, bool rowIsSelected)
{
	g.fillAll(Colours::transparentBlack);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroLiveStatus" componentName=""
                 parentClasses="public Component, public Timer, public ZeroCommandManager::Listener, public TableListBoxModel"
                 constructorParams="ZeroCommandManager *_zeroCommandManager" variableInitialisers="zeroCommandManager(_zeroCommandManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="128" initialHeight="100">
  <METHODS>
    <METHOD name="visibilityChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="66000000"/>
  <GENERICCOMPONENT name="params" id="993933fc9d199187" memberName="list" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 0M" class="TableListBox" params="&quot;params&quot;, this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
