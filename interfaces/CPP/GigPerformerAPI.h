#pragma once

#include <vector>
#include "GigPerformerFunctions.h"

// Override the desired callbacks defined here in your main class (DLLMain.h)
class GigPerformerAPI : public GigPerformerFunctions
{
   public:
      
      // Use this to register callbacks and to do any other setup you need
      virtual void Initialization() {}  
      virtual std::string GetProductDescription() = 0; // This MUST be defined in your class


   public:
      // Notification callbacks to library

      virtual void OnEditStateChanged(bool inEditState) {}
      virtual void OnModeChanged(int mode) { }

      virtual void OnSwitchToPanelView() { }
      virtual void OnSwitchToWiringView() { }
      virtual void OnTunerModeChanged(bool visible) { }
      virtual void OnGlobalPlayStateChanged(bool playing) { }
      virtual void OnWidgetValueChanged(const std::string & widgetName, double newValue) { }
      virtual void OnWidgetStateChanged(const std::string & widgetName, int newState) { }
      virtual void OnWidgetCaptionChanged(const std::string & widgetName, const std::string & newCaption) { }
      virtual void OnMidiDeviceListChanged( std::vector< std::string> & inputs,   std::vector< std::string> & outputs) { } // A midi device was added or removed
      virtual bool OnMidiIn(const std::string & deviceName, const uint8_t* data, int length) { return false; }
      virtual void OnStatusChanged(ExternalAPI_GPStatus status) { } 
      virtual void OnSetlistChanged(const std::string & newSetlistName) {}
      virtual void OnSongChanged(int oldIndex, int newIndex) { } // Called when we have a new song
      virtual void OnSongPartChanged(int oldIndex, int newIndex) { } // Called when we switch to a new song part
      virtual void OnRackspaceActivated() { }
      virtual void OnVariationChanged(int oldIndex, int newIndex) { }
      virtual void OnOpen() { }
      virtual void OnClose() { }
      
   public:
      // Functions that Gig Performer needs to be able to call in your library - override as appropriate

      // These are for inserting panels into a Gig Performer rackspace
      virtual int GetPanelCount() { return 0; } // Returns how many panels your library provides
      virtual std::string GetPanelName(int index) { return ""; } // Return the name of the panel at this index   0..panelCount - 1
      virtual std::string GetPanelXML(int index)  { return ""; } // Return XML representation of a panel 

      // These are for creating menu items in Gig Performer that can be used to trigger external functions provided by the extension developer
      virtual int GetMenuCount() { return 0; }  // Return the number of menu items available
      virtual std::string GetMenuName(int index) { return ""; } // Return the name of menu item at index
      virtual void InvokeMenu(int itemIndex) {}                 // invoke the action associated with menu item at index

   public:
      GigPerformerAPI(LibraryHandle handle) : GigPerformerFunctions(handle) {}
      virtual ~GigPerformerAPI() {}
};
