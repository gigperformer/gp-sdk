// ***************************** IMPORTANT ************************************
// * Place your implementation in the LibMain.h file                          *
// * This file defines all the functions that are exported by the DLL         *
// * The developer does not need to touch this file                           *
// ****************************************************************************

#include "gigperformer/sdk/GigPerformerAPI.h"
#include "gigperformer/sdk/exports.h"
#include "gigperformer/sdk/imports.h"
#include "gigperformer/sdk/macros.h"
#include <stdio.h>

#include <vector>

using namespace gigperformer::sdk;

static GigPerformerAPI *subclass = nullptr;

// You must implement this function so that GP can get information about this
// library to determine whether it should be loaded for user These functions are
// all declared in the C interface file called exports.h

extern "C" EXPORTED void GPQueryLibrary(char *xmlInfoBuffer, int bufferLength)
{
    subclass = CreateGPExtension(nullptr);
    std::string info = subclass->GetProductDescription();
    snprintf(xmlInfoBuffer, bufferLength, "%s", info.c_str());
    delete subclass;
}

// You MUST implement this function call AND call the
// InitializeImportedFunctions function
extern "C" EXPORTED void GPRegister(TGetGPFunctionType getGPFunctionAddress, LibraryHandle handle)
{
    InitializeImportedFunctions(handle, getGPFunctionAddress);
    subclass = CreateGPExtension(handle);
    subclass->Initialization();
}

extern "C" EXPORTED int RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                                             ExternalAPI_GPScriptFunctionDefinition **list)
{
    int count = subclass->RequestGPScriptFunctionSignatureList(location, list);
    return count;
}

extern "C" EXPORTED int GetPanelCount()
{
    return subclass->GetPanelCount();
}

extern "C" EXPORTED int GetPanelName(int index, char *buffer, int bufferLength)
{
    std::string s = subclass->GetPanelName(index);
    int requiredLength = snprintf(buffer, bufferLength, "%s", s.c_str());
    return requiredLength;
}

// One may in fact have to call this one twice - the first time to find out how
// large the buffer REALLY needs to be
extern "C" EXPORTED int GetPanelXML(int index, char *buffer, int bufferLength)
{
    std::string xml = subclass->GetPanelXML(index);
    int requiredLength = snprintf(buffer, bufferLength, "%s", xml.c_str());
    return requiredLength;
}

extern "C" EXPORTED int GetMenuCount()
{
    return subclass->GetMenuCount();
}

extern "C" EXPORTED int GetMenuName(int index, char *buffer, int bufferLength)
{
    std::string s = subclass->GetMenuName(index);
    int requiredLength = snprintf(buffer, bufferLength, "%s", s.c_str());
    return requiredLength;
}

extern "C" EXPORTED void InvokeMenu(int index)
{
    subclass->InvokeMenu(index);
}

/////

extern "C" EXPORTED bool OnMidiIn(const char *deviceName, const uint8_t *data, int length)
{
    std::string name = deviceName;

    return subclass->OnMidiIn(name, data, length);
}

// Called when Gig Performer is about to shut down
extern "C" EXPORTED void OnClose()
{
    subclass->OnClose();
    delete subclass; // Just for tidyness
}

// Called when user enters or exits editing mode.
extern "C" EXPORTED void OnEditStateChanged(bool inEditMode)
{
    subclass->OnEditStateChanged(inEditMode);
}

// called when the user switches into the diagram/connection mode
extern "C" EXPORTED void OnSwitchToWiringView()
{
    subclass->OnSwitchToWiringView();
}

// Called when the user switches into rackspace mode
extern "C" EXPORTED void OnSwitchToPanelView()
{
    subclass->OnSwitchToPanelView();
}

// Called when the global tempo is changed
extern "C" EXPORTED void OnTempoChanged(double newBPM)
{
    subclass->OnTempoChanged(newBPM);
}

// Called when the user switches into setlist mode
extern "C" EXPORTED void OnModeChanged(int mode)
{
    subclass->OnModeChanged(mode);
}

// Called when something changes in GP that we can notify the external API
extern "C" EXPORTED void OnStatusChanged(GPStatusType status)
{
    subclass->OnStatusChanged(status);
}

// Called when a MIDI device is connected or disconnected from the computer
extern "C" EXPORTED void OnMidiDeviceListChanged(const char **inputs, int inputCount, const char **outputs,
                                                 int outputCount)
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
extern "C" EXPORTED void OnOpen()
{
    subclass->OnOpen();
}

// Called when user switches to a new rackspace
extern "C" EXPORTED void OnRackspaceActivated()
{
    subclass->OnRackspaceActivated();
}

// Called when user switches to a new song in setlist mode
extern "C" EXPORTED void OnSongChanged(int oldIndex, int newIndex)
{
    subclass->OnSongChanged(oldIndex, newIndex);
}
// Called when we have a new song

// Called when user switches to a new song part within the current song in
// setlist mode
extern "C" EXPORTED void OnSongPartChanged(int oldIndex, int newIndex)
{
    subclass->OnSongPartChanged(oldIndex, newIndex);
}

extern "C" EXPORTED void OnSetlistChanged(const char *newSetlistName)
{
    std::string name = newSetlistName;
    subclass->OnSetlistChanged(name);
}

// Called when the user switches in or out of tuner mode
extern "C" EXPORTED void OnTunerModeChanged(bool visible)
{
    subclass->OnTunerModeChanged(visible);
}

extern "C" EXPORTED void OnGlobalPlayStateChanged(double playing)
{
    subclass->OnGlobalPlayStateChanged(playing);
}

// Called when user switches from one variation to another
extern "C" EXPORTED void OnVariationChanged(int oldIndex, int newIndex)
{
    subclass->OnVariationChanged(oldIndex, newIndex);
}

// Called when a widget is turned or otherwise adjusted. The library must
// register its interest in listening for such changes
extern "C" EXPORTED void OnWidgetValueChanged(const char *widgetName, double newValue)
{
    std::string name = widgetName;
    subclass->OnWidgetValueChanged(name, newValue);
}

// Called when a widget caption is changed. The library must register its
// interest in listening for such changes
extern "C" EXPORTED void OnWidgetCaptionChanged(const char *widgetName, const char *newCaption)
{
    std::string name = widgetName;
    subclass->OnWidgetCaptionChanged(name, newCaption);
}

// Called when a widget is turned or otherwise adjusted. The library must
// register its interest in listening for such changes
extern "C" EXPORTED void OnWidgetStateChanged(const char *widgetName, int newState)
{
    std::string name = widgetName;
    subclass->OnWidgetStateChanged(name, newState);
}
