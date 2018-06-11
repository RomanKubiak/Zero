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
#include "../JuceLibraryCode/JuceHeader.h"
#include "VLCWrapper.h"
#include "Zero.h"

class ZeroVideoOverlay;
class ZeroCommandManager;
class ZeroMain;

class ZeroConfigDownloader : public Thread
{
	public:
		ZeroConfigDownloader(ZeroMain &_owner);
		~ZeroConfigDownloader();
		void setUrl(const String &_playUrl) { playUrl = _playUrl; }
		void run();
		const String &getConfig() { return downloadedData; }
	private:
		ZeroMain &owner;
		URL playUrl;
		String downloadedData;
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
An auto-generated component, created by the Projucer.

Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ZeroMain  : public Component,
                  public AsyncUpdater,
                  public Logger,
                  public Button::Listener,
                  public Slider::Listener
{
public:
    //==============================================================================
    ZeroMain (ZeroVideoOverlay *_overlay);
    ~ZeroMain();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void handleAsyncUpdate();
	void logMessage(const String &message);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void moved() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ZeroVideoOverlay *overlay;
	ZeroCommandManager *zeroCommandManager;
	ScopedPointer<ZeroConfigDownloader> zeroConfigDownloader;
	var jsonConfig;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<VLCWrapper> vlc;
    ScopedPointer<TextButton> btnPlay;
    ScopedPointer<TextEditor> zeroUrl;
    ScopedPointer<TextEditor> consoleOutput;
    ScopedPointer<TextButton> btnI2CScan;
    ScopedPointer<Slider> cameraPan;
    ScopedPointer<Slider> cameraTilt;
    ScopedPointer<TextButton> btnReqHealth;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroMain)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
