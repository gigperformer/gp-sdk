/// \file    imports.h
/// \brief   These are functions implemented inside Gig Performer and may be called by the extension.
///          They will be initialized when GP is started by calling InitializeImportedFunctions().

#pragma once

#include "gigperformer/sdk/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /// \brief   Call this to initialize all the function variables defined below.
    extern void InitializeImportedFunctions(LibraryHandle handle, TGetGPFunctionType getGPFunction);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Function type definitions

    typedef int (*TGP_GetPathToMe)(LibraryHandle h, char *returnBuffer, int bufferLength);

    typedef int (*TGP_GetPluginList)(LibraryHandle h, char *returnBuffer, int bufferLength, bool useGlobalRackspace);
    typedef bool (*TGP_PluginExists)(LibraryHandle h, const char *pluginHandle, bool useGlobalRackspace);
    typedef void (*TGP_SetPluginParameter)(LibraryHandle h, const char *pluginHandle, int parameterIndex, double value,
                                           bool useGlobalRackspace);
    typedef double (*TGP_GetPluginParameter)(LibraryHandle h, const char *pluginHandle, int parameterIndex,
                                             bool useGlobalRackspace);
    typedef int (*TGP_GetPluginParameterCount)(LibraryHandle h, const char *pluginHandle, bool useGlobalRackspace);
    typedef int (*TGP_GetPluginParameterName)(LibraryHandle h, const char *pluginHandle, int parameterIndex,
                                              char *returnBuffer, int bufferLength, bool useGlobalRackspace);
    typedef int (*TGP_GetPluginParameterText)(LibraryHandle h, const char *pluginHandle, int parameterIndex,
                                              char *returnBuffer, int bufferLength, bool useGlobalRackspace);
    typedef void (*TGP_MapWidgetToPluginParameter)(LibraryHandle h, const char *widgetName, const char *pluginHandle,
                                                   int parameterNumber, bool useGlobalRackspace);

    typedef int (*TGP_GetWidgetList)(LibraryHandle h, char *returnBuffer, int bufferLength, bool useGlobalRackspace);
    typedef bool (*TGP_WidgetExists)(LibraryHandle h, const char *widgetName);
    typedef double (*TGP_GetWidgetValue)(LibraryHandle h, const char *widgetName);
    typedef double (*TGP_GetWidgetTextValue)(LibraryHandle h, const char *widgetName, char *returnBuffer,
                                             int bufferLength);
    typedef bool (*TGP_SetWidgetValue)(LibraryHandle h, const char *widgetName, double newValue);
    typedef bool (*TGP_SetWidgetCaption)(LibraryHandle h, const char *widgetName, const char *newCaption);
    typedef int (*TGP_GetWidgetCaption)(LibraryHandle h, const char *widgetName, char *returnBuffer, int bufferLength);
    typedef void (*TGP_SetWidgetHideOnPresentation)(LibraryHandle h, const char *widgetName, bool hide);
    typedef bool (*TGP_GetWidgetHideState)(LibraryHandle h, const char *widgetName);
    typedef bool (*TGP_ListenForWidget)(LibraryHandle h, const char *widgetName, bool listen);
    typedef bool (*TGP_ListeningForWidget)(LibraryHandle h, const char *widgetName);
    typedef void (*TGP_SetWidgetFillColor)(LibraryHandle h, const char *widgetName, int color);
    typedef void (*TGP_SetWidgetOutlineColor)(LibraryHandle h, const char *widgetName, int color);
    typedef void (*TGP_SetWidgetOutlineThickness)(LibraryHandle h, const char *widgetName, int thickness);
    typedef void (*TGP_SetWidgetOutlineRoundness)(LibraryHandle h, const char *widgetName, int roundness);
    typedef int (*TGP_GetWidgetFillColor)(LibraryHandle h, const char *widgetName);
    typedef int (*TGP_GetWidgetOutlineColor)(LibraryHandle h, const char *widgetName);
    typedef int (*TGP_GetWidgetOutlineThickness)(LibraryHandle h, const char *widgetName);
    typedef int (*TGP_GetWidgetOutlineRoundness)(LibraryHandle h, const char *widgetName);
    typedef void (*TGP_SetWidgetBounds)(LibraryHandle h, const char *widgetName, int left, int top, int width,
                                         int height);
    typedef void (*TGP_GetWidgetBounds)(LibraryHandle h, const char *widgetName, int *left, int *top, int *width,
                                         int *height);

    typedef int (*TGP_RGBAToColor)(LibraryHandle h, double red, double green, double blue, double alpha);
    typedef void (*TGP_ColorToRGBA)(LibraryHandle h, int color, double *red, double *green, double *blue,
                                    double *alpha);

    typedef void (*TGP_SetBPM)(LibraryHandle h, double bpm);
    typedef double (*TGP_GetBPM)(LibraryHandle h);
    typedef void (*TGP_GetCurrentTimeSignature)(LibraryHandle h, int *numerator, int *denominator);

    typedef void (*TGP_Panic)(LibraryHandle h);

    typedef bool (*TGP_ListenForMidi)(LibraryHandle h, const char *deviceName, bool listen);
    typedef bool (*TGP_ListeningForMidi)(LibraryHandle h, const char *deviceName);
    typedef int (*TGP_GetMidiInDeviceCount)(LibraryHandle h);
    typedef int (*TGP_GetMidiInDeviceName)(LibraryHandle h, int index, char *returnBuffer, int bufferLength);
    typedef int (*TGP_GetMidiOutDeviceCount)(LibraryHandle h);
    typedef int (*TGP_GetMidiOutDeviceName)(LibraryHandle h, int index, char *returnBuffer, int bufferLength);
    typedef int (*TGP_TextToHexString)(LibraryHandle h, const char *text, uint8_t *returnBuffer, int bufferLength);
    typedef void (*TGP_SendMidiMessageToMidiOutDevice)(LibraryHandle h, const char *deviceName, const uint8_t *midiData,
                                                       int length);
    typedef void (*TGP_InjectMidiMessageToMidiInputDevice)(LibraryHandle h, const char *deviceName,
                                                           const uint8_t *midiData, int length);
    typedef void (*TGP_InjectMidiMessageToMidiInputAlias)(LibraryHandle h, const char *rigManagerAlias,
                                                          const uint8_t *midiData, int length);

    typedef int (*TGP_GetSongCount)(LibraryHandle h);
    typedef int (*TGP_GetSongName)(LibraryHandle h, int atSongIndex, char *returnBuffer, int bufferLength);
    typedef int (*TGP_GetArtistName)(LibraryHandle h, int atSongIndex, char *returnBuffer, int bufferLength);

    typedef int (*TGP_GetCurrentSongIndex)(LibraryHandle h);
    typedef int (*TGP_GetSongUuid)(LibraryHandle h, int atIndex, char *returnBuffer, int bufferLength);
    typedef int (*TGP_GetVariationNameForSongPart)(LibraryHandle h, int atSongIndex, int atPartIndex,
                                                   char *returnBuffer, int bufferLength);

    typedef int (*TGP_GetSongpartCount)(LibraryHandle h, int atSongIndex);
    typedef int (*TGP_GetChordProFilenameForSong)(LibraryHandle h, int atSongIndex, char *returnBuffer,
                                                  int bufferLength);
    typedef int (*TGP_GetSongpartName)(LibraryHandle h, int atSongIndex, int atIndex, char *returnBuffer,
                                       int bufferLength);
    typedef int (*TGP_GetCurrentSongpartIndex)(LibraryHandle h);

    typedef bool (*TGP_InSetlistMode)(LibraryHandle h);
    typedef bool (*TGP_SwitchToSong)(LibraryHandle h, int songIndex, int partIndex);
    typedef bool (*TGP_SwitchToSongPart)(LibraryHandle h, int partIndex);
    typedef int (*TGP_GetSetlistCount)(LibraryHandle h);
    typedef int (*TGP_GetSetlistName)(LibraryHandle h, int atSongIndex, char *returnBuffer, int bufferLength);
    typedef int (*TGP_GetCurrentSetlistIndex)(LibraryHandle h);
    typedef bool (*TGP_SwitchToSetlist)(LibraryHandle h, int setlistIndex);

    typedef void (*TGP_ConsoleLog)(LibraryHandle h, const char *message);
    typedef void (*TGP_ScriptLog)(LibraryHandle h, const char *message, bool openLogWindow);

    typedef int (*TGP_GetInstanceName)(LibraryHandle h, char *returnBuffer, int bufferLength);

    typedef int (*TGP_GetRackspaceCount)(LibraryHandle h);
    typedef int (*TGP_GetRackspaceName)(LibraryHandle h, int atIndex, char *returnBuffer, int bufferLength);
    typedef int (*TGP_GetCurrentRackspaceIndex)(LibraryHandle h);
    typedef int (*TGP_GetRackspaceUuid)(LibraryHandle h, int atIndex, char *returnBuffer, int bufferLength);
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

    typedef void (*TGP_EnableMetronome)(LibraryHandle h, bool enable);
    typedef bool (*TGP_MetronomeEnabled)(LibraryHandle h);

    typedef bool (*TGP_SaveGigUnconditionally)(LibraryHandle h, bool withTimestamp);
    typedef bool (*TGP_LoadGigByIndex)(LibraryHandle h, int indexNumber);

    typedef bool (*TGP_Tap)(LibraryHandle h);
    typedef void (*TGP_SetPlayheadState)(LibraryHandle h, bool play);
    typedef bool (*TGP_GetPlayheadState)(LibraryHandle h);
    typedef bool (*TGP_Next)(LibraryHandle h);
    typedef bool (*TGP_Previous)(LibraryHandle h);
    typedef bool (*TGP_ResetWidgetToDefault)(LibraryHandle h, const char *widgetName, double newDefault);
    typedef bool (*TGP_RegisterCallback)(LibraryHandle h, const char *callbackName);
    typedef bool (*TGP_UnregisterCallback)(LibraryHandle h, const char *callbackName);

    typedef int (*TGP_VM_PopInteger)(GPRuntimeEngine *vm);
    typedef void (*TGP_VM_PushInteger)(GPRuntimeEngine *vm, int value);
    typedef double (*TGP_VM_PopDouble)(GPRuntimeEngine *vm);
    typedef void (*TGP_VM_PushDouble)(GPRuntimeEngine *vm, double value);
    typedef void (*TGP_VM_PopString)(GPRuntimeEngine *vm, char *buffer, int bufferLength);
    typedef void (*TGP_VM_PushString)(GPRuntimeEngine *vm, const char *buffer);
    typedef bool (*TGP_VM_PopBoolean)(GPRuntimeEngine *vm);
    typedef void (*TGP_VM_PushBoolean)(GPRuntimeEngine *vm, bool value);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Interacting with the GPScript runtime

    /// \brief   Pop an integer associated with function argument.
    extern TGP_VM_PopInteger GP_VM_PopInteger;

    /// \brief   Push an integer associated with function return value.
    extern TGP_VM_PushInteger GP_VM_PushInteger;

    /// \brief   Pop a double associated with function argument.
    extern TGP_VM_PopDouble GP_VM_PopDouble;

    /// \brief   Push a double associated with function return value.
    extern TGP_VM_PushDouble GP_VM_PushDouble;

    /// \brief   Pop a string associated with function argument.
    extern TGP_VM_PopString GP_VM_PopString;

    /// \brief   Push a string associated with function return value.
    extern TGP_VM_PushString GP_VM_PushString;

    /// \brief   Pop a boolean associated with function argument.
    extern TGP_VM_PopBoolean GP_VM_PopBoolean;

    /// \brief   Push a boolean associated with function return value.
    extern TGP_VM_PushBoolean GP_VM_PushBoolean;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Callbacks

    /// \brief   Specify the name of the callback function to be called when the respective event occurs. The callback
    ///          must be implemented in your library as an exported function with a name known to GP.
    extern TGP_RegisterCallback GP_RegisterCallback;

    /// \brief   Inform GP that you no longer want to be called back when the respective event occurs.
    extern TGP_UnregisterCallback GP_UnregisterCallback;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Switching between Gig Performer views

    /// \brief   Switch into or out of tuner view.
    extern TGP_ShowTuner GP_ShowTuner;

    /// \brief   Indicates whether the tuner is visible.
    extern TGP_TunerShowing GP_TunerShowing;

    /// \brief   Enable or disable the metronome.
    extern TGP_EnableMetronome GP_EnableMetronome;

    /// \brief   Indicates whether the metronome is enabled.
    extern TGP_MetronomeEnabled GP_MetronomeEnabled;

    /// \brief   Switch Gig Performer to Setlist View.
    extern TGP_SwitchToSetlistView GP_SwitchToSetlistView;

    /// \brief   Switch Gig Performer to the plugin wiring view.
    extern TGP_SwitchToWiringView GP_SwitchToWiringView;

    /// \brief   Switch Gig Performer to the front panel and widgets view.
    extern TGP_SwitchToPanelView GP_SwitchToPanelView;

    /// \brief   Query GP to see if it is in setlist mode.
    extern TGP_InSetlistMode GP_InSetlistMode;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Interacting with plugins

    /// \brief   Get a list of all plugins defined (i.e, with handles) in the currently active rackspace or in the
    ///          global rackspace.
    /// \return  The actual number of characters needed to store the return value.
    extern TGP_GetPluginList GP_GetPluginList;

    /// \brief   Indicates whether a plugin with the given handle exists in the currently active rackspace or in the
    ///          global rackspace.
    extern TGP_PluginExists GP_PluginExists;

    /// \brief   Set a parameter value for a plugin with the given handle in the currently active rackspace or in the
    ///          global rackspace.
    extern TGP_SetPluginParameter GP_SetPluginParameter;

    /// \brief   Returns the value of the given parameter in the plugin with the given handle in the currently active
    ///          rackspace or in the global rackspace.
    extern TGP_GetPluginParameter GP_GetPluginParameter;

    /// \brief   Returns the number of parameters exposed by the plugin with the given handle in the currently active
    ///          rackspace or in the global rackspace.
    extern TGP_GetPluginParameterCount GP_GetPluginParameterCount;

    /// \brief   Returns the name of the parameter at the specified parameter number of the plugin with the given handle
    ///          in the currently active rackspace or in the global rackspace.
    extern TGP_GetPluginParameterName GP_GetPluginParameterName;

    /// \brief   Returns the current text value of the parameter at the specified parameter number of the plugin with
    /// the given handle
    ///          in the currently active rackspace or in the global rackspace.
    extern TGP_GetPluginParameterText GP_GetPluginParameterText;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Interacting with Widgets

    /// \brief   Map the named widget to the specified parameter number of the plugin with the given handle
    ///          in the currently active rackspace or in the global rackspace.
    extern TGP_MapWidgetToPluginParameter GP_MapWidgetToPluginParameter;

    /// \brief   Get a list of all widgets defined (i.e, with handles) in the currently active or the global rackspace.
    /// \return  The actual number of characters needed to store the return value.
    extern TGP_GetWidgetList GP_GetWidgetList;

    /// \brief   Query GP to see if a widget with the given name exists in the currently active rackspace
    extern TGP_WidgetExists GP_WidgetExists;

    /// \brief   Get the current value (widget position) of the named widget
    extern TGP_GetWidgetValue GP_GetWidgetValue;

    /// \brief   Get the current text value of the named widget.
    /// \details The text value may not be numeric if the parameter connected to this widget provides one.
    /// \return  The actual number of characters needed in the return buffer.
    extern TGP_GetWidgetTextValue GP_GetWidgetTextValue;

    /// \brief   Set the value of a named widget.
    extern TGP_SetWidgetValue GP_SetWidgetValue;

    /// \brief   Resets a widget back to its predefined default value if newDefault is -1. If newDefault is between 0.0
    ///          and 1.0 then save this as new default value but do not change the widget value.
    extern TGP_ResetWidgetToDefault GP_ResetWidgetToDefault;

    /// \brief   Set the label for a widget.
    extern TGP_SetWidgetCaption GP_SetWidgetCaption;

    /// \brief   Get the label for a widget.
    /// \details The library must provide a character buffer and indicate its size. GP will fill in the buffer with the
    ///          caption.
    /// \return  The actual number of characters needed for the return buffer.
    extern TGP_GetWidgetCaption GP_GetWidgetCaption;

    /// \brief   Set whether a widget is hidden when not in Edit mode.
    extern TGP_SetWidgetHideOnPresentation GP_SetWidgetHideOnPresentation;

    /// \brief   Get the current status of whether the named widget is hidden when not in Edit mode.
    extern TGP_GetWidgetHideState GP_GetWidgetHideState;

    /// \brief   Tell GP to call (or stop calling) the OnWidgetValueChanged() callback for the named widget.
    extern TGP_ListenForWidget GP_ListenForWidget;

    /// \brief   Query GP to see if you are listening for widget changes.
    extern TGP_ListeningForWidget GP_ListeningForWidget;

    /// \brief   Set the fill color of widgets that support it.
    extern TGP_SetWidgetFillColor GP_SetWidgetFillColor;

    /// \brief   Set the outline color of widgets that support it.
    extern TGP_SetWidgetOutlineColor GP_SetWidgetOutlineColor;

    /// \brief   Set the outline thickness of widgets that support it.
    extern TGP_SetWidgetOutlineThickness GP_SetWidgetOutlineThickness;

    /// \brief   Set the outline roundness of widgets that support it.
    extern TGP_SetWidgetOutlineRoundness GP_SetWidgetOutlineRoundness;

    /// \brief   Get the fill color of widgets that support it.
    extern TGP_GetWidgetFillColor GP_GetWidgetFillColor;

    /// \brief   Get the outline color of widgets that support it.
    extern TGP_GetWidgetOutlineColor GP_GetWidgetOutlineColor;

    /// \brief   Get the outline thickness of widgets that support it.
    extern TGP_GetWidgetOutlineThickness GP_GetWidgetOutlineThickness;

    /// \brief   Get the outline roundness of widgets that support it.
    extern TGP_GetWidgetOutlineRoundness GP_GetWidgetOutlineRoundness;

    /// \brief   Get the position and size of the named widget.
    extern TGP_GetWidgetBounds GP_GetWidgetBounds;

    /// \brief   Set the position and size of the named widget.
    extern TGP_SetWidgetBounds GP_SetWidgetBounds;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Working with colors

    /// \brief   Convert RGB + Alpha values (all between 0.0 and 1.0) into a color code that can be used to set colors
    ///          in Gig Performer, where available.
    extern TGP_RGBAToColor GP_RGBAToColor;

    /// \brief   Convert a GP color code into RGB + Alpha values (each between 0.0 and 1.0).
    extern TGP_ColorToRGBA GP_ColorToRGBA;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    MIDI

    /// \brief   Tell GP to call (or stop calling) the OnMidiIn callback when MIDI events arrive at the specified device
    ///          name.
    extern TGP_ListenForMidi GP_ListenForMidi;

    /// \brief   Query GP to see if you are listening for MIDI events from a specified device name
    extern TGP_ListeningForMidi GP_ListeningForMidi;

    /// \brief   Query GP for the number of available MIDI In devices.
    extern TGP_GetMidiInDeviceCount GP_GetMidiInDeviceCount;

    /// \brief   Query GP for the name of a MIDI Input device at the specified index (zero-based).
    /// \details The library must provide a character buffer and indicate its size.
    ///          GP will fill in the buffer with the name.
    /// \return  The return value represents the actual length needed to fill the buffer.
    extern TGP_GetMidiInDeviceName GP_GetMidiInDeviceName;

    /// \brief   Query GP for the number of available MIDI Out devices.
    extern TGP_GetMidiOutDeviceCount GP_GetMidiOutDeviceCount;

    /// \brief   Query GP for the name of a MIDI Output device at the specified index (zero-based).
    /// \details The caller must provide a character buffer and indicate its size.
    ///          GP will fill in the buffer with the name.
    /// \return  The return value represents the actual length needed to fill the buffer.
    extern TGP_GetMidiOutDeviceName GP_GetMidiOutDeviceName;

    /// \brief   Send a MIDI message to the specified MIDI Output device.
    ///          It is the callers responsibility to ensure that the message is valid.
    extern TGP_SendMidiMessageToMidiOutDevice GP_SendMidiMessageToMidiOutDevice;

    /// \brief   Convert ASCII text into a hex string, suitable for including in a SysEx message
    extern TGP_TextToHexString GP_TextToHexString;

    /// \brief   Insert a MIDI message into Gig Performer such that GP will respond to it as if it actually came from
    ///          the specified device. It is the caller's responsibility to ensure that the message is valid.
    extern TGP_InjectMidiMessageToMidiInputDevice GP_InjectMidiMessageToMidiInputDevice;

    /// \brief   Insert a MIDI message into Gig Performer such that GP will respond to it as if it actually came from
    ///          the specified Rig Manager global name/alias. It is the caller's responsibility to ensure that the
    ///          message is valid.
    extern TGP_InjectMidiMessageToMidiInputAlias GP_InjectMidiMessageToMidiInputAlias;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Rackspaces and Songs

    /// \brief   Query GP for the list of songs currently available.
    extern TGP_GetSongCount GP_GetSongCount;

    /// \brief   Query GP for the name of a song at the given index (zero-based). The caller must provide a character
    ///          buffer and indicate its size. GP will fill in the buffer with the name.
    /// \return  represents the actual length needed to fill the buffer.
    extern TGP_GetSongName GP_GetSongName;

    /// \brief   Get the artist name of the song at the given index.
    extern TGP_GetArtistName GP_GetArtistName;

    /// \brief   Get the full path to a ChordPro file associated with the song at the given index of the currently
    ///          active setlist.
    /// \return  The number of bytes written to returnBuffer.
    extern TGP_GetChordProFilenameForSong GP_GetChordProFilenameForSong;

    /// \brief   Query GP for the index of the currently selected song.
    extern TGP_GetCurrentSongIndex GP_GetCurrentSongIndex;

    /// \brief   Get the uuid for the song at the given index.
    extern TGP_GetSongUuid GP_GetSongUuid;

    /// \brief   Query GP for the name of the variation associated with the song and song part with the given
    ///          (zero-based) indices.
    extern TGP_GetVariationNameForSongPart GP_GetVariationNameForSongPart;

    /// \brief   Query GP for the number of song parts in the song at the given index.
    extern TGP_GetSongpartCount GP_GetSongpartCount;

    /// \brief   Query GP for the name of the song part at the specified (zero-based) index of the specified song. The
    ///          caller must provide a character buffer and indicate its size. GP will fill in the buffer with the name.
    /// \return  represents the actual length needed to fill the buffer.
    extern TGP_GetSongpartName GP_GetSongpartName;

    /// \brief   Query GP for the index of the currently selected song part index.
    extern TGP_GetCurrentSongpartIndex GP_GetCurrentSongpartIndex;

    /// \brief   Tell GP to switch to the song and song part with the given (zero-based) indices.
    extern TGP_SwitchToSong GP_SwitchToSong;

    /// \brief   Tell GP to switch to the song part with the given (zero-based) index in the current song.
    extern TGP_SwitchToSongPart GP_SwitchToSongPart;

    /// \brief   Returns the number of setlists in the currently gig file.
    extern TGP_GetSetlistCount GP_GetSetlistCount;

    /// \brief   Gets the name of the setlist at the given index.
    /// \return  The number of bytes written to returnBuffer.
    extern TGP_GetSetlistName GP_GetSetlistName;

    /// \brief   Returns the index of the current setlist.
    extern TGP_GetCurrentSetlistIndex GP_GetCurrentSetlistIndex;

    /// \brief   Switch to the setlist defined by the index.
    /// \return  True if Gig Performer has successfully switched to the given setlist.
    extern TGP_SwitchToSetlist GP_SwitchToSetlist;

    /// \brief   Returns the number of rackspaces in the gig file.
    extern TGP_GetRackspaceCount GP_GetRackspaceCount;

    /// \brief   Get the name of rackspace at the given index.
    extern TGP_GetRackspaceName GP_GetRackspaceName;

    /// \brief   Get the rackspace currently in use.
    extern TGP_GetCurrentRackspaceIndex GP_GetCurrentRackspaceIndex;

    /// \brief   Get the uuid for the rackspace at the given index.
    extern TGP_GetRackspaceUuid GP_GetRackspaceUuid;

    /// \brief   Get the rackspace currently in use.
    extern TGP_GetCurrentVariationIndex GP_GetCurrentVariationIndex;

    /// \brief   Get the number of variations in the given rackspace.
    extern TGP_GetVariationCount GP_GetVariationCount;

    /// \brief   Get the name of a specific variation at the given rackspace index.
    extern TGP_GetVariationName GP_GetVariationName;

    /// \brief   Switch to the given rackspace and variation.
    /// \return  true if successful, false else
    extern TGP_SwitchToRackspace GP_SwitchToRackspace;

    /// \brief   Switch to the named rackspace and variation.
    /// \return  true if successful, false else
    extern TGP_SwitchToRackspaceName GP_SwitchToRackspaceName;

    /// \brief   Move to previous variation or rackspace.
    extern TGP_Previous GP_Previous;

    /// \brief   Move to next variation or rackspace.
    extern TGP_Next GP_Next;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Interacting with gig files

    /// \brief   Try to save the file (normally overwriting the existing one). However, if withTimestamp is true, then
    ///          create a subfolder with the same name as the gigfile and save the current file in it, appending the
    ///          current time to it.
    /// \warning Time Stamp not yet implemented
    extern TGP_SaveGigUnconditionally GP_SaveGigUnconditionally;

    /// \brief   Look for a gigfile in a special folder (TBD) that has the prefix indexNumber and try to load it.
    /// \warning Not yet implemented.
    extern TGP_LoadGigByIndex GP_LoadGigByIndex;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Miscellaneous

    /// \brief   Enable or disable the global playhead.
    extern TGP_SetPlayheadState GP_SetPlayheadState;

    /// \brief   Get the global playhead state.
    extern TGP_GetPlayheadState GP_GetPlayheadState;

    /// \brief   Same as clicking the global "Tap Tempo" button.
    extern TGP_Tap GP_Tap;

    /// \brief   Set the global tempo in Gig Performer.
    extern TGP_SetBPM GP_SetBPM;

    /// \brief   Get the global tempo in Gig Performer.
    extern TGP_GetBPM GP_GetBPM;

    /// \brief   Get the current time signature in Gig Performer.
    extern TGP_GetCurrentTimeSignature GP_GetCurrentTimeSignature;

    /// \brief   Stop all notes in the current rackspace.
    extern TGP_Panic GP_Panic;

    /// \brief   Send the message to the console output (works only when Xcode is open).
    extern TGP_ConsoleLog GP_ConsoleLog;

    /// \brief   Display the message in the Script Logger window, possibly opening the window if it is not already open.
    extern TGP_ScriptLog GP_ScriptLog;

    /// \brief   Returns the GP instance name
    extern TGP_GetInstanceName GP_GetInstanceName;

    /// \brief   Returns the folder path where your library is installed.
    /// \details It is useful when you need to access other resource files installed in the same or a relative location
    ///          to the library.
    extern TGP_GetPathToMe GP_GetPathToMe;

#ifdef __cplusplus
}
#endif
