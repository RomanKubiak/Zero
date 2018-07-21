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

#include "ZeroRobotList.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "ZeroCommandManager.h"
//[/MiscUserDefs]

//==============================================================================
ZeroRobotList::ZeroRobotList (ZeroCommandManager *_zeroCommandManager)
    : zeroCommandManager(_zeroCommandManager)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (component = new ListBox ("robotList", this));
    component->setName ("new component");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	component->updateContent();
	robotItemList.add(RemoteRobotItem("Zero @uranus", URL("http://uranus.hopto.org:31337/")));
    //[/Constructor]
}

ZeroRobotList::~ZeroRobotList()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    component = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroRobotList::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroRobotList::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    component->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
	component->setRowHeight(getHeight() / 4);
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
int ZeroRobotList::getNumRows()
{
	return (robotItemList.size());
}

void ZeroRobotList::paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	if (rowIsSelected)
		g.fillAll (Colour(0xff32aca4).withAlpha(0.8f));

	g.setColour(Colours::white);
	g.setFont(height * 0.3f);
	g.drawText(robotItemList[rowNumber].name, 0, 0, width, height * 0.5f, Justification::centredLeft);
	g.setFont(height * 0.15f);
	g.drawText(robotItemList[rowNumber].url.toString(true), 0, height * 0.5f, width, height * 0.5f, Justification::centredLeft);
}

void ZeroRobotList::listBoxItemDoubleClicked (int row, const MouseEvent &e)
{
	if (!robotItemList[row].url.isEmpty())
	{
		zeroCommandManager->connectToRobot(robotItemList[row]);
		if (getParentComponent() && getParentComponent()->getParentComponent())
			getParentComponent()->getParentComponent()->setVisible(false);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroRobotList" componentName=""
                 parentClasses="public Component, public ListBoxModel" constructorParams="ZeroCommandManager *_zeroCommandManager"
                 variableInitialisers="zeroCommandManager(_zeroCommandManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="323e44"/>
  <GENERICCOMPONENT name="new component" id="e4233688aae965c6" memberName="component"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" class="ListBox"
                    params="&quot;robotList&quot;, this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
