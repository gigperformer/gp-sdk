/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class LogWindow  : public Component,
                   public Button::Listener
{
public:
    //==============================================================================
    LogWindow ();
    ~LogWindow() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void static show(); // Call this to show the component
    void static log(const String& text);
    void static finalize(); // Call this when library is about to be unloaded to free resources
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    static LogWindow* sfInstance;

    std::unique_ptr<DocumentWindow> fWindow;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> label;
    std::unique_ptr<TextEditor> txtLog;
    std::unique_ptr<TextButton> btnClear;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LogWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

