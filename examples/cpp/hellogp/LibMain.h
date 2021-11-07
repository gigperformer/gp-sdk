#pragma once
#include <interfaces/C/macros.h>
#include <interfaces/CPP/GigPerformerAPI.h>
#include <interfaces/CPP/GPUtils.h>
#include <interfaces/CPP/GPMidiMessages.h>


// define an XML string describing your product
const std::string XMLProductDescription =   
     // Replace with your information            
    "<Library>" 
    "<Product Name=\"Hello GP - CPP\" Version=\"1.0\" BuildDate=\"12/1/2019\"></Product> "
    "<Description>Briefly describe your product</Description>"
    "<ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>"
    "</Library>"; 

#define then



// This needs to be initialized from the initialization secttion of the LibMain class so it can be used in the standalone functions directly below
// Define your class here - it MUST be called LibMain and it must inherit from GigPerformerAPI

class LibMain : public GigPerformerAPI
{

protected:
    int GetPanelCount() override;
    std::string GetPanelName(int index) override;
    std::string GetPanelXML(int index) override;

    // These are for creating menu items in Gig Performer that can be used to trigger external functions provided by the extension developer
    int GetMenuCount() override;
    std::string GetMenuName(int index) override;
    void InvokeMenu(int itemIndex) override;

public:
    // These must be here but no need to do anything unless you want extra behavior
    LibMain(LibraryHandle handle) : GigPerformerAPI(handle)  { }
    virtual ~LibMain() {}

    void OnSetlistChanged(const std::string & newSetlistName) override
    {
        consoleLog("Setlist switched to: " + newSetlistName);
    }

    void OnModeChanged(int mode) override
    {
       //consoleLog(std::string("Switching to mode: ")  +  ((mode == SetlistMode) ? "Setlist" : "FrontBack" ));
    }

    void OnSwitchToPanelView() override
    {
        consoleLog("Switching to panel view");
        setPlayheadState(true);

        int count = getPluginParameterCount("Legend", false);
        consoleLog(std::to_string(count));

        std::string p1 = getPluginParameterName("Legend", 1, false);
        consoleLog(p1);
    }


    void OnSwitchToWiringView() override
    {
        consoleLog("Switching to wiring view");
        setPlayheadState(false);

    }


    void OnGlobalPlayStateChanged(bool playing) override
    {
        consoleLog(std::string("playing = ") + (playing? " true" : "false"));

        //switchToSetlistView();
        //switchToWiringView();

    }

    // Now, simply override the callback methods in which you are interested
    // and, in the Initialization method at the end of this class, 
    // call RegisterCallback for each of these methods

    void OnWidgetValueChanged(const std::string & widgetName, double newValue) override
    {
        //int noteNumber = (int)GPUtils::Scale(newValue, 0.0, 1.0, 36, 96);
        //GPMidiMessage n = GPMidiMessage::makeNoteOnMessage(noteNumber, 64, 0);
        //const std::string device = "MIDI Monitor (Untitled)";
        //sendMidiMessageToMidiOutDevice(device, n);

        //std::string caption = getWidgetCaption("abc");        
        //consoleLog("caption: " + caption);
        //std::string value = getWidgetTextValue("abc");
        //consoleLog("value: " + value);
        if (widgetName == "abc")
           then
              {
                 consoleLog(std::to_string(newValue)); 
                 setPluginParameter("TheLegend", 34, newValue, false );
              }
        /*
        consoleLog(newValue > 0.5 ? "Yes" : "No");
        if (newValue > 0.5)
           then 
              {
                  if (widgetName == "abc")
                     then next();
                     else previous();
              }
        */
    } 

    // A midi device was added or removed
    void OnMidiDeviceListChanged(std::vector< std::string> & inputs,   std::vector< std::string> & outputs) override
    {
        for (int i = 0; i < inputs.size(); i++)
            {
                std::string & name = inputs[i];
                consoleLog("Input found: " + name);
            }

    }    

    void OnWidgetCaptionChanged(const std::string & widgetName, const std::string & newCaption) override
    {
        consoleLog("Widget caption changed: " + newCaption);
    } 


    // Called when a new gig file has been loaded
    void OnSongChanged(int oldIndex, int newIndex) override
    {
        consoleLog("Song changed from C++ example");
        std::string name  = getSongName(newIndex);
        consoleLog("New song is called " + name);
    }

    void OnWidgetStateChanged(const std::string & widgetName, int newState) override
    {
        consoleLog("Widget " + widgetName + ": " + ((newState == 0) ? "created" : "removed"));
    } 


    void Initialization() override
       {
            // Do any initialization that you need
            
            // .... your code here

              
            // Finally, register all the methods that you are going to actually use, i.e, the ones you declared above as override
            registerCallback("OnSongChanged");
            registerCallback("OnMidiDeviceListChanged");
            registerCallback("OnWidgetValueChanged");
            registerCallback("OnWidgetStateChanged");
            registerCallback("OnWidgetCaptionChanged");
            registerCallback("OnGlobalPlayStateChanged");
            registerCallback("OnModeChanged");
            registerCallback("OnSwitchToPanelView");
            registerCallback("OnSwitchToWiringView");
            registerCallback("OnSetlistChanged");
            listenForWidget("abc", true);           
            listenForWidget("def", true);   


           
            consoleLog("path to library " + getPathToMe());  
       }


    // Generally don't touch this - simply define the constant 'XMLProductDescription' at the top of this file with
    // an XML description of your product
    std::string GetProductDescription() override // This MUST be defined in your class
        {
           return XMLProductDescription;
        }


};