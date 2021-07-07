#include "imports.h"

#include <assert.h>
#include <stdio.h>

#define then

// These are the functions that library developer can call
#ifdef __cplusplus
extern "C"
{
#endif

    TGP_GetPathToMe GP_GetPathToMe;

    TGP_SwitchToSetlistView GP_SwitchToSetlistView;
    TGP_SwitchToWiringView GP_SwitchToWiringView;
    TGP_SwitchToPanelView GP_SwitchToPanelView;

    TGP_GetWidgetList GP_GetWidgetList;
    TGP_WidgetExists GP_WidgetExists;
    TGP_GetWidgetValue GP_GetWidgetValue;
    TGP_GetWidgetTextValue GP_GetWidgetTextValue;
    TGP_SetWidgetValue GP_SetWidgetValue;
    TGP_SetWidgetCaption GP_SetWidgetCaption;
    TGP_GetWidgetCaption GP_GetWidgetCaption;
    TGP_ListenForWidget GP_ListenForWidget;
    TGP_ListeningForWidget GP_ListeningForWidget;
    TGP_ListenForMidi GP_ListenForMidi;
    TGP_ListeningForMidi GP_ListeningForMidi;
    TGP_GetMidiInDeviceCount GP_GetMidiInDeviceCount;
    TGP_GetMidiInDeviceName GP_GetMidiInDeviceName;
    TGP_GetMidiOutDeviceCount GP_GetMidiOutDeviceCount;
    TGP_GetMidiOutDeviceName GP_GetMidiOutDeviceName;
    TGP_TextToHexString GP_TextToHexString;
    TGP_SendMidiMessageToMidiOutDevice GP_SendMidiMessageToMidiOutDevice;
    TGP_InjectMidiMessageToMidiInputDevice GP_InjectMidiMessageToMidiInputDevice;
    TGP_InjectMidiMessageToMidiInputAlias GP_InjectMidiMessageToMidiInputAlias;
    TGP_GetSongCount GP_GetSongCount;
    TGP_GetSongName GP_GetSongName;
    TGP_GetCurrentSongIndex GP_GetCurrentSongIndex;
    TGP_GetSongpartCount GP_GetSongpartCount;
    TGP_GetSongpartName GP_GetSongpartName;
    TGP_GetCurrentSongpartIndex GP_GetCurrentSongpartIndex;
    TGP_InSetlistMode GP_InSetlistMode;
    TGP_SwitchToSong GP_SwitchToSong;
    TGP_SwitchToSongPart GP_SwitchToSongPart;
    TGP_ConsoleLog GP_ConsoleLog;
    TGP_ScriptLog GP_ScriptLog;

    TGP_GetRackspaceCount GP_GetRackspaceCount;
    TGP_GetRackspaceName GP_GetRackspaceName;
    TGP_GetCurrentRackspaceIndex GP_GetCurrentRackspaceIndex;
    TGP_GetCurrentVariationIndex GP_GetCurrentVariationIndex;
    TGP_GetVariationCount GP_GetVariationCount;
    TGP_GetVariationName GP_GetVariationName;

    TGP_SwitchToRackspace GP_SwitchToRackspace;
    TGP_SwitchToRackspaceName GP_SwitchToRackspaceName;

    TGP_ShowTuner GP_ShowTuner;
    TGP_TunerShowing GP_TunerShowing;

    TGP_SaveGigUnconditionally GP_SaveGigUnconditionally;
    TGP_LoadGigByIndex GP_LoadGigByIndex;
    TGP_Tap GP_Tap;
    TGP_Previous GP_Previous;
    TGP_Next GP_Next;

    TGP_ResetWidgetToDefault GP_ResetWidgetToDefault;

    TGP_RegisterCallback GP_RegisterCallback;
    TGP_UnregisterCallback GP_UnregisterCallback;

    static TGetGPFunctionType RequestGPFunctionByName;

    static void *RequestAddress(LibraryHandle handle, const char *functionName)
    {
        char str[255];

        void *p = RequestGPFunctionByName(handle, functionName);

        if (p != NULL)
            then sprintf(str, "%s : found", functionName);
        else
            sprintf(str, "%s : failed", functionName);

        GP_ConsoleLog(handle, str);

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

        R(GP_ShowTuner);
        R(GP_TunerShowing);

        R(GP_GetWidgetList);
        R(GP_WidgetExists);
        R(GP_GetWidgetValue);
        R(GP_GetWidgetTextValue);
        R(GP_SetWidgetValue);
        R(GP_SetWidgetCaption);
        R(GP_GetWidgetCaption);
        R(GP_ListenForWidget);
        R(GP_ListeningForWidget);
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
        R(GP_GetCurrentSongIndex);
        R(GP_GetSongpartCount);
        R(GP_GetSongpartName);
        R(GP_GetCurrentSongpartIndex);
        R(GP_InSetlistMode);
        R(GP_SwitchToSong);
        R(GP_SwitchToSongPart);
        R(GP_ScriptLog);
        R(GP_GetRackspaceCount);
        R(GP_GetRackspaceName);
        R(GP_GetCurrentRackspaceIndex);
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

#undef R
    }

#ifdef __cplusplus
}
#endif
