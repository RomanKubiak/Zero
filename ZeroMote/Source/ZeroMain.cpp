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

#include "ZeroMain.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "ZeroVideoOverlay.h"
#include "ZeroCommandManager.h"

ZeroConfigDownloader::ZeroConfigDownloader(ZeroMain &_owner)
	: owner(_owner), Thread("Config downloader")
{
}

ZeroConfigDownloader::~ZeroConfigDownloader()
{
	if (isThreadRunning())
		stopThread(500);
}

void ZeroConfigDownloader::run()
{
	downloadedData = playUrl.readEntireTextStream(false);

	if (downloadedData.isEmpty())
	{
		_DBG("Failed to download config data from: ");
		_DBG(playUrl.toString(true)+"\n");
		owner.triggerAsyncUpdate();
	}
	else
	{
		_DBG("Download config data, size:%d", downloadedData.length());
		owner.triggerAsyncUpdate();
	}
}
//[/MiscUserDefs]

//==============================================================================
ZeroMain::ZeroMain (ZeroVideoOverlay *_overlay)
    : overlay(_overlay)
{
    //[Constructor_pre] You can add your own custom stuff here..
	Logger::setCurrentLogger(this);
	zeroCommandManager = new ZeroCommandManager();
	overlay->setCommandManager(zeroCommandManager);
    //[/Constructor_pre]

    addAndMakeVisible (vlc = new VLCWrapper());

    addAndMakeVisible (btnPlay = new TextButton ("Play"));
    btnPlay->addListener (this);

    addAndMakeVisible (zeroUrl = new TextEditor ("Zero URL"));
    zeroUrl->setMultiLine (false);
    zeroUrl->setReturnKeyStartsNewLine (false);
    zeroUrl->setReadOnly (false);
    zeroUrl->setScrollbarsShown (true);
    zeroUrl->setCaretVisible (true);
    zeroUrl->setPopupMenuEnabled (true);
    zeroUrl->setColour (TextEditor::backgroundColourId, Colour (0x41ffffff));
    zeroUrl->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    zeroUrl->setColour (TextEditor::outlineColourId, Colour (0x00ffffff));
    zeroUrl->setText (TRANS("http://uranus.hopto.org:31337"));

    addAndMakeVisible (consoleOutput = new TextEditor ("Console"));
    consoleOutput->setMultiLine (true);
    consoleOutput->setReturnKeyStartsNewLine (false);
    consoleOutput->setReadOnly (true);
    consoleOutput->setScrollbarsShown (true);
    consoleOutput->setCaretVisible (false);
    consoleOutput->setPopupMenuEnabled (false);
    consoleOutput->setColour (TextEditor::textColourId, Colours::white);
    consoleOutput->setColour (TextEditor::backgroundColourId, Colour (0xb3000000));
    consoleOutput->setColour (TextEditor::highlightColourId, Colour (0xbf44c4ff));
    consoleOutput->setText (TRANS("Console"));

    addAndMakeVisible (btnI2CScan = new TextButton ("I2C Scan"));
    btnI2CScan->addListener (this);
    btnI2CScan->setColour (TextButton::buttonColourId, Colour (0xff5c88a4));

    addAndMakeVisible (component = new ZeroXYComponent());

    //[UserPreSize]
	consoleOutput->setText(String::empty, false);
	consoleOutput->setFont(Font("Terminus (TTF)",12.0f,Font::plain));
	vlc->attachCallback(overlay);
    //[/UserPreSize]

    setSize (640, 400);


    //[Constructor] You can add your own custom stuff here..
	zeroConfigDownloader = new ZeroConfigDownloader(*this);
    //[/Constructor]
}

ZeroMain::~ZeroMain()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    vlc = nullptr;
    btnPlay = nullptr;
    zeroUrl = nullptr;
    consoleOutput = nullptr;
    btnI2CScan = nullptr;
    component = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
	Logger::setCurrentLogger(nullptr);
    //[/Destructor]
}

//==============================================================================
void ZeroMain::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ZeroMain::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    vlc->setBounds (0, 0, proportionOfWidth (0.7497f), proportionOfHeight (0.5000f));
    btnPlay->setBounds (proportionOfWidth (0.8497f), proportionOfHeight (0.5395f), proportionOfWidth (0.1504f), proportionOfHeight (0.0395f));
    zeroUrl->setBounds (0, proportionOfHeight (0.8997f), proportionOfWidth (0.3996f), 24);
    consoleOutput->setBounds (0, (getHeight() / 2), proportionOfWidth (0.8497f), proportionOfHeight (0.3997f));
    btnI2CScan->setBounds (proportionOfWidth (0.8497f), proportionOfHeight (0.5000f), proportionOfWidth (0.1504f), proportionOfHeight (0.0395f));
    component->setBounds (proportionOfWidth (0.7497f), 0, proportionOfWidth (0.2502f), proportionOfHeight (0.2492f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ZeroMain::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnPlay)
    {
        //[UserButtonCode_btnPlay] -- add your button handler code here..
		_DBG("Trying to download config from: ");
		_DBG(zeroUrl->getText()+"\n");
		zeroConfigDownloader->setUrl(zeroUrl->getText());
		zeroConfigDownloader->startThread();
        //[/UserButtonCode_btnPlay]
    }
    else if (buttonThatWasClicked == btnI2CScan)
    {
        //[UserButtonCode_btnI2CScan] -- add your button handler code here..
		zeroCommandManager->requestI2CScan();
        //[/UserButtonCode_btnI2CScan]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ZeroMain::moved()
{
    //[UserCode_moved] -- Add your code here...
    //[/UserCode_moved]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ZeroMain::handleAsyncUpdate()
{
	if (!zeroConfigDownloader->getConfig().isEmpty())
	{
		Logger::writeToLog(zeroConfigDownloader->getConfig());
		const Result res = JSON::parse(zeroConfigDownloader->getConfig(), jsonConfig);

		if (res.failed())
		{
			_DBG("Failed to parse config as JSON\n");
		}
		else
		{
			zeroCommandManager->setNeuralHost(jsonConfig.getDynamicObject()->getProperty("neural_host"));
			zeroCommandManager->setNeuralPort(jsonConfig.getDynamicObject()->getProperty("neural_port"));
			vlc->loadMedia(jsonConfig.getDynamicObject()->getProperty("video_url"));
			vlc->play();
		}
	}
}

void ZeroMain::logMessage(const String &message)
{
	MessageManagerLock mmlock;
	consoleOutput->insertTextAtCaret(message);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ZeroMain" componentName=""
                 parentClasses="public Component, public AsyncUpdater, public Logger"
                 constructorParams="ZeroVideoOverlay *_overlay" variableInitialisers="overlay(_overlay)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="400">
  <METHODS>
    <METHOD name="moved()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="" id="8a738eb729bd9b3d" memberName="vlc" virtualName=""
                    explicitFocusOrder="0" pos="0 0 74.975% 50%" class="VLCWrapper"
                    params=""/>
  <TEXTBUTTON name="Play" id="1991ccadb6da15cc" memberName="btnPlay" virtualName=""
              explicitFocusOrder="0" pos="84.965% 53.951% 15.035% 3.951%" buttonText="Play"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="Zero URL" id="e1a9b5497fb3dc28" memberName="zeroUrl" virtualName=""
              explicitFocusOrder="0" pos="0 89.97% 39.96% 24" bkgcol="41ffffff"
              hilitecol="0" outlinecol="ffffff" initialText="http://uranus.hopto.org:31337"
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="Console" id="d4b0221a8d721030" memberName="consoleOutput"
              virtualName="" explicitFocusOrder="0" pos="0 0C 84.965% 39.97%"
              textcol="ffffffff" bkgcol="b3000000" hilitecol="bf44c4ff" initialText="Console"
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="0"/>
  <TEXTBUTTON name="I2C Scan" id="952f1fa33f7bc2ef" memberName="btnI2CScan"
              virtualName="" explicitFocusOrder="0" pos="84.965% 50% 15.035% 3.951%"
              bgColOff="ff5c88a4" buttonText="I2C Scan" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <JUCERCOMP name="" id="74306dc57fa5b36a" memberName="component" virtualName=""
             explicitFocusOrder="0" pos="74.975% 0 25.025% 24.924%" sourceFile="ZeroXYComponent.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
