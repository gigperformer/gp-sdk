#pragma once

/*
   These are functions implemented inside Gig Performer and may be called by a
   DLL
*/

#include "GPTypes.h"

#ifdef __cplusplus
using namespace DeskewGP;
#endif

typedef int (*TGP_GetPathToMe)(LibraryHandle h, char *returnBuffer, int bufferLength);

typedef int (*TGP_GetWidgetList)(LibraryHandle h, char *returnBuffer, int bufferLength, bool useGlobalRackspace);

typedef bool (*TGP_WidgetExists)(LibraryHandle h, const char *widgetName);

typedef double (*TGP_GetWidgetValue)(LibraryHandle h, const char *widgetName);

typedef double (*TGP_GetWidgetTextValue)(LibraryHandle h, const char *widgetName, char *returnBuffer, int bufferLength);

typedef bool (*TGP_SetWidgetValue)(LibraryHandle h, const char *widgetName, double newValue);

typedef bool (*TGP_SetWidgetCaption)(LibraryHandle h, const char *widgetName, const char *newCaption);

typedef int (*TGP_GetWidgetCaption)(LibraryHandle h, const char *widgetName, char *returnBuffer, int bufferLength);

typedef bool (*TGP_ListenForWidget)(LibraryHandle h, const char *widgetName, bool listen);

typedef bool (*TGP_ListeningForWidget)(LibraryHandle h, const char *widgetName);

typedef bool (*TGP_ListenForMidi)(LibraryHandle h, const char *deviceName, bool listen);

typedef bool (*TGP_ListeningForMidi)(LibraryHandle h, const char *deviceName);

typedef int (*TGP_GetMidiInDeviceCount)(LibraryHandle h);

typedef int (*TGP_GetMidiInDeviceName)(LibraryHandle h, int index, char *returnBuffer, int bufferLength);

typedef int (*TGP_GetMidiOutDeviceCount)(LibraryHandle h);

typedef int (*TGP_GetMidiOutDeviceName)(LibraryHandle h, int index, char *returnBuffer, int bufferLength);

typedef int (*TGP_TextToHexString)(LibraryHandle h, const char *text, uint8_t *returnBuffer, int bufferLength);

typedef void (*TGP_SendMidiMessageToMidiOutDevice)(LibraryHandle h, const char *deviceName, const uint8_t *midiData,
                                                   int length);

typedef void (*TGP_InjectMidiMessageToMidiInputDevice)(LibraryHandle h, const char *deviceName, const uint8_t *midiData,
                                                       int length);

typedef void (*TGP_InjectMidiMessageToMidiInputAlias)(LibraryHandle h, const char *rigManagerAlias,
                                                      const uint8_t *midiData, int length);

typedef int (*TGP_GetSongCount)(LibraryHandle h);

typedef int (*TGP_GetSongName)(LibraryHandle h, int atSongIndex, char *returnBuffer, int bufferLength);

typedef int (*TGP_GetCurrentSongIndex)(LibraryHandle h);

typedef int (*TGP_GetSongpartCount)(LibraryHandle h, int atSongIndex);

typedef int (*TGP_GetSongpartName)(LibraryHandle h, int atSongIndex, int atIndex, char *returnBuffer, int bufferLength);

typedef int (*TGP_GetCurrentSongpartIndex)(LibraryHandle h);

typedef bool (*TGP_InSetlistMode)(LibraryHandle h);

typedef bool (*TGP_SwitchToSong)(LibraryHandle h, int songIndex, int partIndex);

typedef bool (*TGP_SwitchToSongPart)(LibraryHandle h, int partIndex);

typedef void (*TGP_ConsoleLog)(LibraryHandle h, const char *message);

typedef void (*TGP_ScriptLog)(LibraryHandle h, const char *message, bool openLogWindow);

typedef int (*TGP_GetRackspaceCount)(LibraryHandle h);

typedef int (*TGP_GetRackspaceName)(LibraryHandle h, int atIndex, char *returnBuffer, int bufferLength);

typedef int (*TGP_GetCurrentRackspaceIndex)(LibraryHandle h);

typedef int (*TGP_GetCurrentVariationIndex)(LibraryHandle h);

typedef int (*TGP_GetVariationCount)(LibraryHandle h, int atRackspaceIndex);

typedef int (*TGP_GetVariationName)(LibraryHandle h, int atRackspaceIndex, int atIndex, char *returnBuffer,
                                    int bufferLength);

typedef bool (*TGP_SwitchToRackspace)(LibraryHandle h, int rackspaceIndex, int variationIndex);

typedef bool (*TGP_SwitchToRackspaceName)(LibraryHandle h, const char *rackspaceName, const char *variationName);

typedef void (*TGP_SwitchToSetlistView)(LibraryHandle h);

typedef void (*TGP_SwitchToWiringView)(LibraryHandle h);

typedef void (*TGP_SwitchToPanelView)(LibraryHandle h);

typedef void (*TGP_ShowTuner)(LibraryHandle h, bool show);

typedef bool (*TGP_TunerShowing)(LibraryHandle h);

typedef bool (*TGP_SaveGigUnconditionally)(LibraryHandle h, bool withTimestamp);

typedef bool (*TGP_LoadGigByIndex)(LibraryHandle h, int indexNumber);

typedef bool (*TGP_Tap)(LibraryHandle h);

typedef bool (*TGP_Next)(LibraryHandle h);

typedef bool (*TGP_Previous)(LibraryHandle h);

typedef bool (*TGP_ResetWidgetToDefault)(LibraryHandle h, const char *widgetName, double newDefault);

typedef bool (*TGP_RegisterCallback)(LibraryHandle h, const char *callbackName);

typedef bool (*TGP_UnregisterCallback)(LibraryHandle h, const char *callbackName);

// These are the extern function variables that can be used to call GP functions
// They will be initialized when GP is started by calling
// InitializeImportedFunctions(...)

#ifdef __cplusplus
extern "C"
{
#endif

    extern TGP_RegisterCallback GP_RegisterCallback;
    extern TGP_UnregisterCallback GP_UnregisterCallback;

    extern TGP_GetPathToMe GP_GetPathToMe;

    extern TGP_ShowTuner GP_ShowTuner;
    extern TGP_TunerShowing GP_TunerShowing;

    extern TGP_SwitchToSetlistView GP_SwitchToSetlistView;
    extern TGP_SwitchToWiringView GP_SwitchToWiringView;
    extern TGP_SwitchToPanelView GP_SwitchToPanelView;

    extern TGP_GetWidgetList GP_GetWidgetList;
    extern TGP_WidgetExists GP_WidgetExists;
    extern TGP_GetWidgetValue GP_GetWidgetValue;
    extern TGP_GetWidgetTextValue GP_GetWidgetTextValue;
    extern TGP_SetWidgetValue GP_SetWidgetValue;
    extern TGP_SetWidgetCaption GP_SetWidgetCaption;
    extern TGP_GetWidgetCaption GP_GetWidgetCaption;
    extern TGP_ListenForWidget GP_ListenForWidget;
    extern TGP_ListeningForWidget GP_ListeningForWidget;
    extern TGP_ListenForMidi GP_ListenForMidi;
    extern TGP_ListeningForMidi GP_ListeningForMidi;
    extern TGP_GetMidiInDeviceCount GP_GetMidiInDeviceCount;
    extern TGP_GetMidiInDeviceName GP_GetMidiInDeviceName;
    extern TGP_GetMidiOutDeviceCount GP_GetMidiOutDeviceCount;
    extern TGP_GetMidiOutDeviceName GP_GetMidiOutDeviceName;
    extern TGP_SendMidiMessageToMidiOutDevice GP_SendMidiMessageToMidiOutDevice;
    extern TGP_TextToHexString GP_TextToHexString;
    extern TGP_InjectMidiMessageToMidiInputDevice GP_InjectMidiMessageToMidiInputDevice;
    extern TGP_InjectMidiMessageToMidiInputAlias GP_InjectMidiMessageToMidiInputAlias;
    extern TGP_GetSongCount GP_GetSongCount;
    extern TGP_GetSongName GP_GetSongName;
    extern TGP_GetCurrentSongIndex GP_GetCurrentSongIndex;
    extern TGP_GetSongpartCount GP_GetSongpartCount;
    extern TGP_GetSongpartName GP_GetSongpartName;
    extern TGP_GetCurrentSongpartIndex GP_GetCurrentSongpartIndex;
    extern TGP_InSetlistMode GP_InSetlistMode;
    extern TGP_SwitchToSong GP_SwitchToSong;
    extern TGP_SwitchToSongPart GP_SwitchToSongPart;
    extern TGP_ConsoleLog GP_ConsoleLog;
    extern TGP_ScriptLog GP_ScriptLog;
    extern TGP_GetRackspaceCount GP_GetRackspaceCount;
    extern TGP_GetRackspaceName GP_GetRackspaceName;
    extern TGP_GetCurrentRackspaceIndex GP_GetCurrentRackspaceIndex;
    extern TGP_GetCurrentVariationIndex GP_GetCurrentVariationIndex;
    extern TGP_GetVariationCount GP_GetVariationCount;
    extern TGP_GetVariationName GP_GetVariationName;
    extern TGP_SwitchToRackspace GP_SwitchToRackspace;
    extern TGP_SwitchToRackspaceName GP_SwitchToRackspaceName;
    extern TGP_SaveGigUnconditionally GP_SaveGigUnconditionally;
    extern TGP_LoadGigByIndex GP_LoadGigByIndex;
    extern TGP_Tap GP_Tap;
    extern TGP_Previous GP_Previous;
    extern TGP_Next GP_Next;

    extern TGP_ResetWidgetToDefault GP_ResetWidgetToDefault;

    extern void InitializeImportedFunctions(LibraryHandle handle,
                                            TGetGPFunctionType getGPFunction); // Call this to initialize all the
                                                                               // function variables defined below

#ifdef __cplusplus
}
#endif
