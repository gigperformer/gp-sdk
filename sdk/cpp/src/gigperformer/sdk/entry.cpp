// ***************************** IMPORTANT ************************************
// * Place your implementation in the LibMain.h file                          *
// * This file defines all the functions that are exported by the DLL         *
// * The developer does not need to touch this file                           *
// ****************************************************************************

#include "gigperformer/sdk/GigPerformerAPI.h"
#include "gigperformer/sdk/exports.h"
#include "gigperformer/sdk/imports.h"
#include <stdio.h>

#include <vector>

using namespace gigperformer::sdk;

static GigPerformerAPI *subclass = nullptr;

// You must implement this function so that GP can get information about this
// library to determine whether it should be loaded for user These functions are
// all declared in the C interface file called exports.h

extern "C" void GPQueryLibrary(char *xmlInfoBuffer, int bufferLength)
{
    subclass = CreateGPExtension(nullptr);
    std::string info = subclass->GetProductDescription();
    snprintf(xmlInfoBuffer, bufferLength, "%s", info.c_str());
    delete subclass;
}

// You MUST implement this function call AND call the
// InitializeImportedFunctions function
extern "C" void GPRegister(TGetGPFunctionType getGPFunctionAddress, LibraryHandle handle)
{
    InitializeImportedFunctions(handle, getGPFunctionAddress);
    subclass = CreateGPExtension(handle);
    subclass->Initialization();
}

extern "C" int GetPanelCount()
{
    return subclass->GetPanelCount();
}

extern "C" int GetPanelName(int index, char *buffer, int bufferLength)
{
    std::string s = subclass->GetPanelName(index);
    int requiredLength = snprintf(buffer, bufferLength, "%s", s.c_str());
    return requiredLength;
}

// One may in fact have to call this one twice - the first time to find out how
// large the buffer REALLY needs to be
extern "C" int GetPanelXML(int index, char *buffer, int bufferLength)
{
    std::string xml = subclass->GetPanelXML(index);
    int requiredLength = snprintf(buffer, bufferLength, "%s", xml.c_str());
    return requiredLength;
}

extern "C" int GetMenuCount()
{
    return subclass->GetMenuCount();
}

extern "C" int GetMenuName(int index, char *buffer, int bufferLength)
{
    std::string s = subclass->GetMenuName(index);
    int requiredLength = snprintf(buffer, bufferLength, "%s", s.c_str());
    return requiredLength;
}

extern "C" void InvokeMenu(int index)
{
    subclass->InvokeMenu(index);
}

/////

extern "C" bool OnMidiIn(const char *deviceName, const uint8_t *data, int length)
{
    std::string name = deviceName;

    return subclass->OnMidiIn(name, data, length);
}

// Called when Gig Performer is about to shut down
extern "C" void OnClose()
{
    subclass->OnClose();
    delete subclass; // Just for tidyness
}

// Called when user enters or exits editing mode.
extern "C" void OnEditStateChanged(bool inEditMode)
{
    subclass->OnEditStateChanged(inEditMode);
}

// called when the user switches into the diagram/connection mode
extern "C" void OnSwitchToWiringView()
{
    subclass->OnSwitchToWiringView();
}

// Called when the user switches into rackspace mode
extern "C" void OnSwitchToPanelView()
{
    subclass->OnSwitchToPanelView();
}

// Called when the user switches into setlist mode
extern "C" void OnModeChanged(int mode)
{
    subclass->OnModeChanged(mode);
}

// Called when a new gig file has finished being loaded
extern "C" void OnGigLoaded()
{
    subclass->OnGigLoaded();
}
// Called when a new gig file has been loaded

// Called when a MIDI device is connected or disconnected from the computer
extern "C" void OnMidiDeviceListChanged(const char **inputs, int inputCount, const char **outputs, int outputCount)
{
    std::vector<std::string> inputDevices;

    for (int i = 0; i < inputCount; i++)
        inputDevices.push_back(inputs[i]);

    std::vector<std::string> outputDevices;

    for (int i = 0; i < outputCount; i++)
        outputDevices.push_back(outputs[i]);

    subclass->OnMidiDeviceListChanged(inputDevices, outputDevices);
}
// A midi device was added or removed

// Called when Gig Performer has finished initializing itself
extern "C" void OnOpen()
{
    subclass->OnOpen();
}

// Called when user switches to a new rackspace
extern "C" void OnRackspaceChanged()
{
    subclass->OnRackspaceChanged();
}

// Called when user switches to a new song in setlist mode
extern "C" void OnSongChanged(int oldIndex, int newIndex)
{
    subclass->OnSongChanged(oldIndex, newIndex);
}
// Called when we have a new song

// Called when user switches to a new song part within the current song in
// setlist mode
extern "C" void OnSongPartChanged(int oldIndex, int newIndex)
{
    subclass->OnSongPartChanged(oldIndex, newIndex);
}
// Called when we switch to a new song part

// Called when the user switches in or out of tuner mode
extern "C" void OnTunerModeChanged(bool visible)
{
    subclass->OnTunerModeChanged(visible);
}

extern "C" void OnGlobalPlayStateChanged(bool playing)
{
    subclass->OnGlobalPlayStateChanged(playing);
}

// Called when user switches from one variation to another
extern "C" void OnVariationChanged(int oldIndex, int newIndex)
{
    subclass->OnVariationChanged(oldIndex, newIndex);
}

// Called when a widget is turned or otherwise adjusted. The library must
// register its interest in listening for such changes
extern "C" void OnWidgetValueChanged(const char *widgetName, double newValue)
{
    std::string name = widgetName;
    subclass->OnWidgetValueChanged(name, newValue);
}

// Called when a widget caption is changed. The library must register its
// interest in listening for such changes
extern "C" void OnWidgetCaptionChanged(const char *widgetName, const char *newCaption)
{
    std::string name = widgetName;
    subclass->OnWidgetCaptionChanged(name, newCaption);
}

// Called when a widget is turned or otherwise adjusted. The library must
// register its interest in listening for such changes
extern "C" void OnWidgetStateChanged(const char *widgetName, int newState)
{
    std::string name = widgetName;
    subclass->OnWidgetStateChanged(name, newState);
}
