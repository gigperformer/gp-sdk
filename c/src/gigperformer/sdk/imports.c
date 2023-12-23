#include "gigperformer/sdk/imports.h"
#include "gigperformer/sdk/macros.h"

#include <assert.h>
#include <stdio.h>

#define then

// Declare the function and initialize
#define DeclareFunc(funcName) T##funcName funcName = NULL

// If this is newer than the version expected by GP then a crash may occur. Do NOT change this information.
// In particular, whenever we add new functions into GP that can be called from this SDK
// We need to update this version so we can check that it's safe to call GP
#define GPSDK_VERSION 48

// This is an EXPORT from the DLL but it's here for convenience so it can be picked up by both C and C++ projects
EXPORTED int GetGPSDKVersion(void)
{
    return GPSDK_VERSION;
}

// These are the functions that library developer can call
#ifdef __cplusplus
extern "C"
{
#endif

    DeclareFunc(GP_GetPathToMe);

    DeclareFunc(GP_SwitchToSetlistView);
    DeclareFunc(GP_SwitchToWiringView);
    DeclareFunc(GP_SwitchToPanelView);

    DeclareFunc(GP_GetPluginList);
    DeclareFunc(GP_PluginExists);
    DeclareFunc(GP_SetPluginParameter);
    DeclareFunc(GP_GetPluginParameter);
    DeclareFunc(GP_GetPluginParameterCount);
    DeclareFunc(GP_GetPluginParameterName);
    DeclareFunc(GP_GetPluginParameterText);
    DeclareFunc(GP_GetPluginCaption);
    DeclareFunc(GP_GetPluginName);

    DeclareFunc(GP_SetWidgetHideOnPresentation);
    DeclareFunc(GP_GetWidgetHideState);
    DeclareFunc(GP_MapWidgetToPluginParameter);
    DeclareFunc(GP_GetWidgetList);
    DeclareFunc(GP_WidgetExists);
    DeclareFunc(GP_GetWidgetValue);
    DeclareFunc(GP_GetWidgetTextValue);
    DeclareFunc(GP_SetWidgetValue);
    DeclareFunc(GP_SetWidgetCaption);
    DeclareFunc(GP_GetWidgetCaption);
    DeclareFunc(GP_ListenForWidget);
    DeclareFunc(GP_ListeningForWidget);
    DeclareFunc(GP_SetWidgetFillColor);
    DeclareFunc(GP_SetWidgetOutlineColor);
    DeclareFunc(GP_SetWidgetOutlineThickness);
    DeclareFunc(GP_SetWidgetOutlineRoundness);
    DeclareFunc(GP_GetWidgetFillColor);
    DeclareFunc(GP_GetWidgetOutlineColor);
    DeclareFunc(GP_GetWidgetOutlineThickness);
    DeclareFunc(GP_GetWidgetOutlineRoundness);
    DeclareFunc(GP_SetWidgetBounds);
    DeclareFunc(GP_GetWidgetBounds);

    DeclareFunc(GP_RGBAToColor);
    DeclareFunc(GP_ColorToRGBA);

    DeclareFunc(GP_SetBPM);
    DeclareFunc(GP_GetBPM);
    DeclareFunc(GP_GetCurrentTimeSignature);

    DeclareFunc(GP_Panic);

    DeclareFunc(GP_ListenForMidi);
    DeclareFunc(GP_ListeningForMidi);
    DeclareFunc(GP_GetMidiInDeviceCount);
    DeclareFunc(GP_GetMidiInDeviceName);
    DeclareFunc(GP_GetMidiOutDeviceCount);
    DeclareFunc(GP_GetMidiOutDeviceName);
    DeclareFunc(GP_TextToHexString);
    DeclareFunc(GP_SendMidiMessageToMidiOutDevice);
    DeclareFunc(GP_InjectMidiMessageToMidiInputDevice);
    DeclareFunc(GP_InjectMidiMessageToMidiInputAlias);
    DeclareFunc(GP_GetSongCount);
    DeclareFunc(GP_GetSongName);
    DeclareFunc(GP_GetArtistName);
    DeclareFunc(GP_GetSongKey);
    DeclareFunc(GP_GetSongTempo);
    DeclareFunc(GP_GetChordProFilenameForSong);
    DeclareFunc(GP_GetCurrentSongIndex);
    DeclareFunc(GP_GetSongUuid);
    DeclareFunc(GP_GetVariationNameForSongPart);
    DeclareFunc(GP_GetSongpartCount);
    DeclareFunc(GP_GetSongpartName);
    DeclareFunc(GP_GetCurrentSongpartIndex);
    DeclareFunc(GP_InSetlistMode);
    DeclareFunc(GP_SwitchToSong);
    DeclareFunc(GP_SwitchToSongPart);
    DeclareFunc(GP_GetSetlistCount);
    DeclareFunc(GP_GetSetlistName);
    DeclareFunc(GP_GetCurrentSetlistIndex);
    DeclareFunc(GP_SwitchToSetlist);
    DeclareFunc(GP_ConsoleLog);
    DeclareFunc(GP_ScriptLog);

    DeclareFunc(GP_GetInstanceName);

    DeclareFunc(GP_GetRackspaceCount);
    DeclareFunc(GP_GetRackspaceName);
    DeclareFunc(GP_GetCurrentRackspaceIndex);
    DeclareFunc(GP_GetRackspaceUuid);
    DeclareFunc(GP_GetCurrentVariationIndex);
    DeclareFunc(GP_GetVariationCount);
    DeclareFunc(GP_GetVariationName);

    DeclareFunc(GP_SwitchToRackspace);
    DeclareFunc(GP_SwitchToRackspaceName);

    DeclareFunc(GP_SetPlayheadState);
    DeclareFunc(GP_GetPlayheadState);

    DeclareFunc(GP_ShowTuner);
    DeclareFunc(GP_TunerShowing);

    DeclareFunc(GP_EnableMetronome);
    DeclareFunc(GP_MetronomeEnabled);

    DeclareFunc(GP_SaveGigUnconditionally);
    DeclareFunc(GP_LoadGigByIndex);
    DeclareFunc(GP_Tap);
    DeclareFunc(GP_Previous);
    DeclareFunc(GP_Next);

    DeclareFunc(GP_ResetWidgetToDefault);

    DeclareFunc(GP_RegisterCallback);
    DeclareFunc(GP_UnregisterCallback);

    DeclareFunc(GP_VM_PopInteger);
    DeclareFunc(GP_VM_PushInteger);
    DeclareFunc(GP_VM_PopDouble);
    DeclareFunc(GP_VM_PushDouble);
    DeclareFunc(GP_VM_TopStringLength);
    DeclareFunc(GP_VM_PopString);
    DeclareFunc(GP_VM_PushString);
    DeclareFunc(GP_VM_PopBoolean);
    DeclareFunc(GP_VM_PushBoolean);

    static TGetGPFunctionType RequestGPFunctionByName;

    static void *RequestAddress(LibraryHandle handle, const char *functionName)
    {
        void *p = RequestGPFunctionByName(handle, functionName);

#ifdef DEBUG
        char str[255];

        if (p != NULL)
            then sprintf(str, "%s : found", functionName);
        else
            sprintf(str, "%s : failed", functionName);

        GP_ConsoleLog(handle, str);
#endif

        return p;
    }

    void InitializeImportedFunctions(LibraryHandle handle, TGetGPFunctionType getGPFunction)
    {
        RequestGPFunctionByName = getGPFunction; // This is only needed at the beginning so we can ask GP
                                                 // for the address of all the functions we want

        // If this fails, all bets are off
        GP_ConsoleLog = (TGP_ConsoleLog)RequestGPFunctionByName(handle, "GP_ConsoleLog");
        assert(GP_ConsoleLog != NULL);

// Convenient way to add lots of functions without screwing up
#define R(name) name = (T##name)RequestAddress(handle, #name)

        R(GP_GetPathToMe);

        R(GP_SwitchToSetlistView);
        R(GP_SwitchToWiringView);
        R(GP_SwitchToPanelView);

        R(GP_SetPlayheadState);
        R(GP_GetPlayheadState);

        R(GP_ShowTuner);
        R(GP_TunerShowing);

        R(GP_EnableMetronome);
        R(GP_MetronomeEnabled);

        R(GP_GetPluginList);
        R(GP_PluginExists);
        R(GP_SetPluginParameter);
        R(GP_GetPluginParameter);
        R(GP_GetPluginParameterCount);
        R(GP_GetPluginParameterName);
        R(GP_GetPluginParameterText);
        R(GP_GetPluginCaption);
        R(GP_GetPluginName);

        R(GP_MapWidgetToPluginParameter);
        R(GP_GetWidgetList);
        R(GP_WidgetExists);
        R(GP_GetWidgetValue);
        R(GP_GetWidgetTextValue);
        R(GP_SetWidgetValue);
        R(GP_SetWidgetCaption);
        R(GP_GetWidgetCaption);
        R(GP_SetWidgetHideOnPresentation);
        R(GP_GetWidgetHideState);

        R(GP_ListenForWidget);
        R(GP_ListeningForWidget);

        R(GP_SetWidgetFillColor);
        R(GP_SetWidgetOutlineColor);
        R(GP_SetWidgetOutlineThickness);
        R(GP_SetWidgetOutlineRoundness);
        R(GP_GetWidgetFillColor);
        R(GP_GetWidgetOutlineColor);
        R(GP_GetWidgetOutlineThickness);
        R(GP_GetWidgetOutlineRoundness);
        R(GP_GetWidgetBounds);
        R(GP_SetWidgetBounds);

        R(GP_RGBAToColor);
        R(GP_ColorToRGBA);

        R(GP_SetBPM);
        R(GP_GetBPM);
        R(GP_GetCurrentTimeSignature);

        R(GP_Panic);

        R(GP_ListenForMidi);
        R(GP_ListeningForMidi);
        R(GP_GetMidiInDeviceCount);
        R(GP_GetMidiInDeviceName);
        R(GP_GetMidiOutDeviceCount);
        R(GP_GetMidiOutDeviceName);
        R(GP_TextToHexString);
        R(GP_SendMidiMessageToMidiOutDevice);
        R(GP_InjectMidiMessageToMidiInputDevice);
        R(GP_InjectMidiMessageToMidiInputAlias);
        R(GP_GetSongCount);
        R(GP_GetSongName);
        R(GP_GetArtistName);
        R(GP_GetSongKey);
        R(GP_GetSongTempo);
        R(GP_GetChordProFilenameForSong);
        R(GP_GetCurrentSongIndex);
        R(GP_GetVariationNameForSongPart);
        R(GP_GetSongpartCount);
        R(GP_GetSongpartName);
        R(GP_GetCurrentSongpartIndex);
        R(GP_GetSongUuid);
        R(GP_InSetlistMode);
        R(GP_SwitchToSong);
        R(GP_SwitchToSongPart);
        R(GP_GetSetlistCount);
        R(GP_GetSetlistName);
        R(GP_GetCurrentSetlistIndex);
        R(GP_SwitchToSetlist);
        R(GP_ScriptLog);

        R(GP_GetInstanceName);

        R(GP_GetRackspaceCount);
        R(GP_GetRackspaceName);
        R(GP_GetCurrentRackspaceIndex);
        R(GP_GetRackspaceUuid);
        R(GP_GetCurrentVariationIndex);
        R(GP_GetVariationCount);
        R(GP_GetVariationName);

        R(GP_SwitchToRackspace);
        R(GP_SwitchToRackspaceName);

        R(GP_SaveGigUnconditionally);
        R(GP_LoadGigByIndex);
        R(GP_Tap);
        R(GP_Previous);
        R(GP_Next);

        R(GP_ResetWidgetToDefault);

        R(GP_RegisterCallback);
        R(GP_UnregisterCallback);

        R(GP_VM_PopInteger);
        R(GP_VM_PushInteger);
        R(GP_VM_PopDouble);
        R(GP_VM_PushDouble);
        R(GP_VM_TopStringLength);
        R(GP_VM_PopString);
        R(GP_VM_PushString);
        R(GP_VM_PopBoolean);
        R(GP_VM_PushBoolean);

#undef R
    }

#ifdef __cplusplus
}
#endif
