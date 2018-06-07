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

#include "ZeroXYComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ZeroXYComponent::ZeroXYComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (111, 111);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ZeroXYComponent::~ZeroXYComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ZeroXYComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x02000000));

    //[UserPaint] Add your own custom painting code here..
	g.setColour(Colours::pink);
	g.strokePath(indicatorPath, PathStrokeType(2.0f));
    //[/UserPaint]
}

void ZeroXYComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ZeroXYComponent::mouseMove (const MouseEvent& e)
{
    //[UserCode_mouseMove] -- Add your code here...
    //[/UserCode_mouseMove]
}

void ZeroXYComponent::mouseEnter (const MouseEvent& e)
{
    //[UserCode_mouseEnter] -- Add your code here...
    //[/UserCode_mouseEnter]
}

void ZeroXYComponent::mouseExit (const MouseEvent& e)
{
    //[UserCode_mouseExit] -- Add your code here...
    //[/UserCode_mouseExit]
}

void ZeroXYComponent::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	Desktop::getInstance().setMousePosition(getScreenBounds().getCentre());
	setMouseCursor(MouseCursor::NoCursor);
    //[/UserCode_mouseDown]
}

void ZeroXYComponent::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	indicatorPath.clear();
	indicatorPath.addArrow(
		Line<float>(Point<float>(getWidth() / 2.0f, getHeight() / 2.0f), e.getPosition().toFloat()),
		1.5f,
		8.0f,
		8.0f);
	lastMouseDrag = e.getPosition();
	repaint();
    //[/UserCode_mouseDrag]
}

void ZeroXYComponent::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
	Desktop::getInstance().setMousePosition(getScreenBounds().getCentre());
	setMouseCursor(MouseCursor::NormalCursor);
	indicatorPath.clear();
	repaint();
    //[/UserCode_mouseUp]
}

void ZeroXYComponent::mouseDoubleClick (const MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
    //[/UserCode_mouseDoubleClick]
}

void ZeroXYComponent::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel)
{
    //[UserCode_mouseWheelMove] -- Add your code here...
    //[/UserCode_mouseWheelMove]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroXYComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="111" initialHeight="111">
  <METHODS>
    <METHOD name="mouseEnter (const MouseEvent&amp; e)"/>
    <METHOD name="mouseMove (const MouseEvent&amp; e)"/>
    <METHOD name="mouseExit (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
    <METHOD name="mouseWheelMove (const MouseEvent&amp; e, const MouseWheelDetails&amp; wheel)"/>
  </METHODS>
  <BACKGROUND backgroundColour="2000000"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
