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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "Zero.h"
class ZeroCommandManager;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ZeroRobotList  : public Component,
                       public ListBoxModel
{
public:
    //==============================================================================
    ZeroRobotList (ZeroCommandManager *_zeroCommandManager);
    ~ZeroRobotList();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int getNumRows() override;
	void paintListBoxItem (int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
	void listBoxItemDoubleClicked (int row, const MouseEvent &) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Array <RemoteRobotItem> robotItemList;
	ZeroCommandManager *zeroCommandManager;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ListBox> component;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroRobotList)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
