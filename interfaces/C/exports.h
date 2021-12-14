#pragma once

#include "macros.h"
#include "GPTypes.h"


#ifdef __cplusplus
using namespace DeskewGP;
#endif

/*
 GPQuery, which MUST be implemented by the library is the first thing called by Gig Performer.
 It is expecting back a short XML file with information specified as below. This information will be
 presented to the user who can decide whether this particular library should be used
<Library>
    <Product name="My Control Surface" Version="1.0" BuildDate="12/1/2019"></Product>
    <Description>This product does blah blah blah</Description>
    <ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>
</Library>
*/



#ifdef __cplusplus
extern "C"
{
#endif


EXPORTED void GPQueryLibrary(char* xmlInfoBuffer, int bufferLength);

EXPORTED int GPGetSDKVersion(); // We test to make sure this is available, otherwise we know SDK is too old

// Called by GP during startup to get a list of GP Script functions implemented by a library



// If the user decides that this library should be used then it will call GPRegister
// It passes in the address of a function
// that the library developer can call to request the address of other functions that Gig Performer
// makes available to the developer. The handle that is passed in must be saved and all GP function
// calls that are used by the library will pass in that handle as the first parameter
// The XML buffer is used to let the library developer provide multiple items of interest

EXPORTED void GPRegister(TGetGPFunctionType getGPFunctionAddress, LibraryHandle handle);


// Optional calls that DLL may provide depending on functionality.

// Define a list of GP function signatures along with the addresses of their respective implementations. The location is used to indicate which kind of script entity is asking for the functions. Return the number of entries
extern "C"  EXPORTED  int RequestGPScriptFunctionSignatureList( GPScript_AllowedLocations location, ExternaAPI_GPScriptFunctionDefinition* *list); // Improved version



// Note that for the strings, we return how long the strings NEED to be so that GP can call again with a longer buffer if necessary
// Panel creation
EXPORTED int GetPanelCount();
EXPORTED int GetPanelName(int index, char* buffer, int bufferLength); // DLL fills in the buffer up to bufferLength (including 0 terminator)
EXPORTED int GetPanelXML(int index, char* buffer, int bufferLength); // Return panel layout in XML format

// For extension driven submenus to be inserted in Extensions toplevel menu
EXPORTED int GetMenuCount();
EXPORTED int GetMenuName(int index, char* buffer, int bufferLength);
EXPORTED void InvokeMenu(int index);

// Callbacks from Gig Performer into the DLL
// Only implement the callbacks in which you are interested
   
   
// Called when a MIDI event arrives from a device for which the library has registered its interest in listening
// Returns whether the midi event should be passed on to the next handler
EXPORTED    bool OnMidiIn(const char*  deviceName, const uint8_t* data, int length);

// Called when Gig Performer is about to shut down
EXPORTED    void OnClose();

// Called when user enters or exits editing mode. 
EXPORTED    void OnEditStateChanged(bool inEditState);

// called when the user switches into the diagram/connection mode
EXPORTED    void OnSwitchToWiringView();

// Called when the user switches into rackspace mode
EXPORTED    void OnSwitchToPanelView();

// Called when the user switches into or out of setlist mode - modes defined in macros.h
EXPORTED    void OnModeChanged(int mode);  

// Called when something in GP changes that can trigger a notification to the external API
EXPORTED    void OnStatusChanged(GPStatusType status); 

// Called when the user changes the setlist
EXPORTED    void OnSetlistChanged(const char* newSetlistName); 

// Called when a MIDI device is connected or disconnected from the computer. You get an array of strings for the midiin and midiout device list respectively
EXPORTED    void OnMidiDeviceListChanged(const char** inputs, int intputCount, const char** outputs, int outputCount); // A midi device was added or removed - get the new list

// Called when Gig Performer has finished initializing itself
EXPORTED    void OnOpen();

// Called when user switches to a new rackspace
EXPORTED    void OnRackspaceActivated();

// Called when user switches to a new song in setlist mode
EXPORTED    void OnSongChanged(int oldIndex, int newIndex); // Called when we have a new song

// Called when user switches to a new song part within the current song in setlist mode
EXPORTED    void OnSongPartChanged(int oldIndex, int newIndex); // Called when we switch to a new song part

// Called when the user switches in or out of tuner mode
EXPORTED    void OnTunerModeChanged(bool visible);

// Called when user switches from one variation to another
EXPORTED    void OnVariationChanged(int oldIndex, int newIndex);

// Called when a widget is turned or otherwise adjusted. The library must register its interest in listening for such changes
EXPORTED    void OnWidgetValueChanged(const char*  widgetName, double newValue);

// Called when a widget is created (handle defined = 0) or destroyed (handle removed = 1). The library must register its interest in listening for such changes
EXPORTED    void OnWidgetStateChanged(const char*  widgetName, int newState);

// Called when a widget caption changes. The library must register its interest in listening for such changes
EXPORTED    void OnWidgetCaptionChanged(const char*  widgetName, const char* newCaption);


#ifdef __cplusplus
}
#endif