#pragma once

#include "gigperformer/sdk/macros.h"
#include "gigperformer/sdk/types.h"

/*
 GPQuery, which MUST be implemented by the library is the first thing called by
 Gig Performer. It is expecting back a short XML file with information specified
 as below. This information will be presented to the user who can decide whether
 this particular library should be used
<Library>
    <Product name="My ControlSurface" Version="1.0" BuildDate="12/1/2019"></Product>
    <Description>Thisproduct does blah blah blah</Description>
    <ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>
</Library>
*/

#ifdef __cplusplus
extern "C"
{
#endif

    void GPQueryLibrary(char *xmlInfoBuffer, int bufferLength);

    // If the user decides that this library should be used then it will call
    // GPRegister It passes in the address of a function that the library
    // developer can call to request the address of other functions that Gig
    // Performer makes available to the developer. The handle that is passed in
    // must be saved and all GP function calls that are used by the library will
    // pass in that handle as the first parameter The XML buffer is used to let
    // the library developer provide multiple items of interest

    void GPRegister(TGetGPFunctionType getGPFunctionAddress, LibraryHandle handle);

    // Optional calls that DLL may provide depending on functionality.
    // Note that for the strings, we return how long the strings NEED to be so
    // that GP can call again with a longer buffer if necessary Panel creation
    int GetPanelCount();
    int GetPanelName(int index, char *buffer,
                     int bufferLength); // DLL fills in the buffer up to bufferLength (including
                                        // 0 terminator)
    int GetPanelXML(int index, char *buffer,
                    int bufferLength); // Return panel layout in XML format

    // For extension driven submenus to be inserted in Extensions toplevel menu
    int GetMenuCount();
    int GetMenuName(int index, char *buffer, int bufferLength);
    void InvokeMenu(int index);

    // Callbacks from Gig Performer into the DLL
    // Only implement the callbacks in which you are interested

    // Called when a MIDI event arrives from a device for which the library has
    // registered its interest in listening Returns whether the midi event should
    // be passed on to the next handler
    bool OnMidiIn(const char *deviceName, const uint8_t *data, int length);

    // Called when Gig Performer is about to shut down
    void OnClose();

    // Called when user enters or exits editing mode.
    void OnEditStateChanged(bool inEditState);

    // called when the user switches into the diagram/connection mode
    void OnSwitchToWiringView();

    // Called when the user switches into rackspace mode
    void OnSwitchToPanelView();

    // Called when the user switches into or out of setlist mode - modes defined
    // in macros.h
    void OnModeChanged(int mode);

    // Called when a new gig file has finished being loaded
    void OnGigLoaded(); // Called when a new gig file has been loaded

    // Called when a MIDI device is connected or disconnected from the computer.
    // You get an array of strings for the midiin and midiout device list
    // respectively
    void OnMidiDeviceListChanged(const char **inputs, int intputCount, const char **outputs,
                                 int outputCount); // A midi device was added or removed - get the new list

    // Called when Gig Performer has finished initializing itself
    void OnOpen();

    // Called when user switches to a new rackspace
    void OnRackspaceChanged();

    // Called when user switches to a new song in setlist mode
    void OnSongChanged(int oldIndex,
                       int newIndex); // Called when we have a new song

    // Called when user switches to a new song part within the current song in
    // setlist mode
    void OnSongPartChanged(int oldIndex,
                           int newIndex); // Called when we switch to a new song part

    // Called when the user switches in or out of tuner mode
    void OnTunerModeChanged(bool visible);

    // Called when user switches from one variation to another
    void OnVariationChanged(int oldIndex, int newIndex);

    // Called when a widget is turned or otherwise adjusted. The library must
    // register its interest in listening for such changes
    void OnWidgetValueChanged(const char *widgetName, double newValue);

    // Called when a widget is created (handle defined = 0) or destroyed (handle
    // removed = 1). The library must register its interest in listening for such
    // changes
    void OnWidgetStateChanged(const char *widgetName, int newState);

    // Called when a widget caption changes. The library must register its
    // interest in listening for such changes
    void OnWidgetCaptionChanged(const char *widgetName, const char *newCaption);

#ifdef __cplusplus
}
#endif
