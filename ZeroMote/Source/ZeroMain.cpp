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
		_ERR("Failed to download config data from: " + playUrl.toString(true) + "\n");
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
    btnPlay->setConnectedEdges (Button::ConnectedOnRight);
    btnPlay->addListener (this);

    addAndMakeVisible (zeroUrl = new TextEditor ("Zero URL"));
    zeroUrl->setMultiLine (false);
    zeroUrl->setReturnKeyStartsNewLine (false);
    zeroUrl->setReadOnly (false);
    zeroUrl->setScrollbarsShown (false);
    zeroUrl->setCaretVisible (false);
    zeroUrl->setPopupMenuEnabled (false);
    zeroUrl->setColour (TextEditor::textColourId, Colour (0xffe1f8ff));
    zeroUrl->setColour (TextEditor::backgroundColourId, Colour (0xa2000000));
    zeroUrl->setColour (TextEditor::highlightColourId, Colour (0x00000000));
    zeroUrl->setColour (TextEditor::outlineColourId, Colour (0x75ffffff));
    zeroUrl->setColour (TextEditor::shadowColourId, Colour (0x91fcfcfc));
    zeroUrl->setText (TRANS("http://uranus.hopto.org:31337"));

    addAndMakeVisible (consoleOutput = new TextEditor ("Console"));
    consoleOutput->setMultiLine (true);
    consoleOutput->setReturnKeyStartsNewLine (false);
    consoleOutput->setReadOnly (true);
    consoleOutput->setScrollbarsShown (true);
    consoleOutput->setCaretVisible (false);
    consoleOutput->setPopupMenuEnabled (false);
    consoleOutput->setColour (TextEditor::textColourId, Colour (0xffe9e9e9));
    consoleOutput->setColour (TextEditor::backgroundColourId, Colour (0xff161616));
    consoleOutput->setColour (TextEditor::highlightColourId, Colour (0xbf44c4ff));
    consoleOutput->setText (TRANS("Console"));

    addAndMakeVisible (btnI2CScan = new TextButton ("I2C Scan"));
    btnI2CScan->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    btnI2CScan->addListener (this);
    btnI2CScan->setColour (TextButton::buttonColourId, Colour (0xff5c88a4));

    addAndMakeVisible (btnReqHealth = new TextButton ("Request Health"));
    btnReqHealth->setTooltip (TRANS("Request Health"));
    btnReqHealth->setButtonText (TRANS("Health"));
    btnReqHealth->setConnectedEdges (Button::ConnectedOnLeft);
    btnReqHealth->addListener (this);
    btnReqHealth->setColour (TextButton::buttonColourId, Colour (0xff099c85));


    //[UserPreSize]
	consoleOutput->setText(String::empty, false);
	consoleOutput->setFont(Font("Terminus (TTF)",12.0f,Font::bold));
	vlc->attachCallback(overlay);
    //[/UserPreSize]

    setSize (600, 600);


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
    btnReqHealth = nullptr;


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

    vlc->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (0.4500f));
    btnPlay->setBounds (0, proportionOfHeight (0.4500f), proportionOfWidth (0.2000f), proportionOfHeight (0.0500f));
    zeroUrl->setBounds (0, proportionOfHeight (0.5000f), proportionOfWidth (1.0000f), proportionOfHeight (0.0500f));
    consoleOutput->setBounds (0, proportionOfHeight (0.5500f), proportionOfWidth (1.0000f), proportionOfHeight (0.4500f));
    btnI2CScan->setBounds (proportionOfWidth (0.2000f), proportionOfHeight (0.4500f), proportionOfWidth (0.2000f), proportionOfHeight (0.0500f));
    btnReqHealth->setBounds (proportionOfWidth (0.4000f), proportionOfHeight (0.4500f), proportionOfWidth (0.2000f), proportionOfHeight (0.0500f));
    //[UserResized] Add your own custom resize handling here..
	overlay->setSize(vlc->getWidth(), vlc->getHeight());
    //[/UserResized]
}

void ZeroMain::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnPlay)
    {
        //[UserButtonCode_btnPlay] -- add your button handler code here..
		_DBG("Trying to download config from: "+zeroUrl->getText()+"\n");
		zeroCommandManager->setActive(false);
		zeroConfigDownloader->setUrl(zeroUrl->getText());
		zeroConfigDownloader->startThread();
        //[/UserButtonCode_btnPlay]
    }
    else if (buttonThatWasClicked == btnI2CScan)
    {
        //[UserButtonCode_btnI2CScan] -- add your button handler code here..
        //[/UserButtonCode_btnI2CScan]
    }
    else if (buttonThatWasClicked == btnReqHealth)
    {
        //[UserButtonCode_btnReqHealth] -- add your button handler code here..
		zeroCommandManager->requestHealth();
        //[/UserButtonCode_btnReqHealth]
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
			_ERR("Failed to parse config as JSON\n");
			zeroCommandManager->setActive(false);

		}
		else
		{
			zeroCommandManager->setNeuralHost(jsonConfig.getDynamicObject()->getProperty("neural_host"));
			zeroCommandManager->setNeuralPort(jsonConfig.getDynamicObject()->getProperty("neural_port"));
			vlc->loadMedia(jsonConfig.getDynamicObject()->getProperty("video_url"));
			vlc->play();
			zeroCommandManager->setActive(true);
			zeroCommandManager->setRemoteMode();
		}
	}
	else
	{
		zeroCommandManager->setActive(false);
	}
}

void ZeroMain::logMessage(const String &message)
{
	MessageManagerLock mmlock;
	if (message.startsWith("ERR"))
		consoleOutput->setColour(TextEditor::textColourId, Colour (0xfff74949));
	if (message.startsWith("DBG"))
		consoleOutput->setColour(TextEditor::textColourId, Colour (0xff22e42c));

	consoleOutput->insertTextAtCaret(message.substring(3));

	consoleOutput->setColour(TextEditor::textColourId, Colours::white);
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
                 fixedSize="1" initialWidth="600" initialHeight="600">
  <METHODS>
    <METHOD name="moved()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="" id="8a738eb729bd9b3d" memberName="vlc" virtualName=""
                    explicitFocusOrder="0" pos="0 0 100% 45%" class="VLCWrapper"
                    params=""/>
  <TEXTBUTTON name="Play" id="1991ccadb6da15cc" memberName="btnPlay" virtualName=""
              explicitFocusOrder="0" pos="0 45% 20% 5%" buttonText="Play" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="Zero URL" id="e1a9b5497fb3dc28" memberName="zeroUrl" virtualName=""
              explicitFocusOrder="0" pos="0 50% 100% 5%" textcol="ffe1f8ff"
              bkgcol="a2000000" hilitecol="0" outlinecol="75ffffff" shadowcol="91fcfcfc"
              initialText="http://uranus.hopto.org:31337" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="0" popupmenu="0"/>
  <TEXTEDITOR name="Console" id="d4b0221a8d721030" memberName="consoleOutput"
              virtualName="" explicitFocusOrder="0" pos="0 55% 100% 45%" textcol="ffe9e9e9"
              bkgcol="ff161616" hilitecol="bf44c4ff" initialText="Console"
              multiline="1" retKeyStartsLine="0" readonly="1" scrollbars="1"
              caret="0" popupmenu="0"/>
  <TEXTBUTTON name="I2C Scan" id="952f1fa33f7bc2ef" memberName="btnI2CScan"
              virtualName="" explicitFocusOrder="0" pos="20% 45% 20% 5%" bgColOff="ff5c88a4"
              buttonText="I2C Scan" connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Request Health" id="1cb0da407fff16d2" memberName="btnReqHealth"
              virtualName="" explicitFocusOrder="0" pos="40% 45% 20% 5%" tooltip="Request Health"
              bgColOff="ff099c85" buttonText="Health" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
