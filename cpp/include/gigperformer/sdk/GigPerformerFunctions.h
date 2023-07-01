/// \file    GigPerformerFunctions.h
/// \brief   Contains the definitions of the GigPerformerFunctions class.

#pragma once

#include <string>
#include <vector>

#include "gigperformer/sdk/GPMidiMessages.h"
#include "gigperformer/sdk/imports.h"

namespace gigperformer
{
namespace sdk
{

/// \brief   The member functions of this class can be called from the extension
class GigPerformerFunctions
{
  public:
    explicit GigPerformerFunctions(LibraryHandle handle);
    virtual ~GigPerformerFunctions();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Callbacks

    /// \brief   Specify the name of the callback function to be called when the respective event occurs. The callback
    ///          must be implemented in your library as an exported function with a name known to GP.
    bool registerCallback(const std::string &callbackName);

    /// \brief   Inform GP that you no longer want to be called back when the respective event occurs.
    bool unregisterCallback(const std::string &callbackName);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Switching between Gig Performer views

    /// \brief   Switch into or out of tuner view.
    void showTuner(bool show);

    /// \brief   Indicates whether the tuner is visible.
    bool tunerShowing();

    /// \brief   Enable or disable the metronome.
    void enableMetronome(bool enable);

    /// \brief   Indicates whether the metronome is enabled.
    bool metronomeEnabled();

    /// \brief   Switch Gig Performer to Setlist View.
    void switchToSetlistView();

    /// \brief   Switch Gig Performer to the plugin wiring view.
    void switchToWiringView();

    /// \brief   Switch Gig Performer to the front panel and widgets view.
    void switchToPanelView();

    /// \brief   Query GP to see if it is in setlist mode.
    bool inSetlistMode();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Widgets

    /// \brief   Get a list of all widgets defined (i.e, with handles) in the currently active or the global rackspace.
    void getWidgetList(std::vector<std::string> &list, bool useGlobalRackspace);

    /// \brief   Query GP to see if a widget with the given name exists in the currently active rackspace
    bool widgetExists(const std::string &widgetName);

    /// \brief   Get the current value (widget position) of the named widget
    double getWidgetValue(const std::string &widgetName);

    /// \brief   Get the current text value of the named widget.
    /// \details The text value may not be numeric if the parameter connected to this widget provides one.
    std::string getWidgetTextValue(const std::string &widgetName);

    /// \brief   Set the value of a named widget.
    bool setWidgetValue(const std::string &widgetName, double newValue);

    /// \brief   Resets a widget back to its predefined default value if newDefault is -1. If newDefault is between 0.0
    ///          and 1.0 then save this as new default value but do not change the widget value.
    bool resetWidgetToDefault(const std::string &widgetName, double newDefault = -1);

    /// \brief   Set the label for a widget.
    bool setWidgetCaption(const std::string &widgetName, const std::string &newCaption);

    /// \brief   Get the label for a widget.
    std::string getWidgetCaption(const std::string &widgetName);

    /// \brief   Tell GP to call (or stop calling) the OnWidgetValueChanged() callback for the named widget.
    bool listenForWidget(const std::string &widgetName, bool listen);

    /// \brief   Query GP to see if you are listening for widget changes.
    bool listeningForWidget(const std::string &widgetName);

    /// \brief   Map the named widget to the specified parameter number of the plugin with the given handle.
    void mapWidgetToPluginParameter(const std::string &widgetName, const std::string &pluginHandle, int parameterNumber,
                                    bool useGlobalRackspace);

    /// \brief   Set the fill color of widgets that support it.
    void setWidgetFillColor(const std::string &widgetName, int color);

    /// \brief   Set the outline color of widgets that support it.
    void setWidgetOutlineColor(const std::string &widgetName, int color);

    /// \brief   Set the outline thickness of widgets that support it.
    void setWidgetOutlineThickness(const std::string &widgetName, int thickness);

    /// \brief   Set the outline roundness of widgets that support it.
    void setWidgetOutlineRoundness(const std::string &widgetName, int roundness);

    /// \brief   Get the fill color of widgets that support it.
    int getWidgetFillColor(const std::string &widgetName);

    /// \brief   Get the outline color of widgets that support it.
    int getWidgetOutlineColor(const std::string &widgetName);

    /// \brief   Get the outline thickness of widgets that support it.
    int getWidgetOutlineThickness(const std::string &widgetName);

    /// \brief   Get the outline roundness of widgets that support it.
    int getWidgetOutlineRoundness(const std::string &widgetName);

    /// \brief   Get the position and size of the named widget.
    void getWidgetBounds(const std::string &widgetName, int &left, int &top, int &width, int &height);

    /// \brief   Set the position and size of the named widget.
    void setWidgetBounds(const std::string &widgetName, int left, int top, int width, int height);

    /// \brief   Set whether a widget is hidden when not in Edit mode.
    void setWidgetHideOnPresentation(const std::string &widgetName, bool hide);

    /// \brief   Get the current status of whether the named widget is hidden when not in Edit mode.
    bool getWidgetHideState(const std::string &widgetName);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Working with colors

    /// \brief   Convert RGB + Alpha values (all between 0.0 and 1.0) into a color code that can be used to set colors
    ///          in Gig Performer, where available.
    int RGBAToColor(double red, double green, double blue, double alpha);

    /// \brief   Convert a GP color code into RGB + Alpha values (each between 0.0 and 1.0).
    void ColorToRGBA(int color, double &red, double &green, double &blue, double &alpha);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    MIDI

    /// \brief   Tell GP to call (or stop calling) the OnMidiIn callback when MIDI events arrive at the specified device
    ///          name.
    bool listenForMidi(const std::string &deviceName, bool listen);

    /// \brief   Query GP to see if you are listening for MIDI events from a specified device name
    bool listeningForMidi(const std::string &deviceName);

    /// \brief   Query GP for the number of available MIDI In devices.
    int getMidiInDeviceCount();

    /// \brief   Query GP for the name of a MIDI Input device at the specified index (zero-based).
    std::string getMidiInDeviceName(int index);

    /// \brief   Query GP for the number of available MIDI Out devices.
    int getMidiOutDeviceCount();

    /// \brief   Query GP for the name of a MIDI Output device at the specified index (zero-based).
    std::string getMidiOutDeviceName(int index);

    /// \brief   Send a MIDI message to the specified MIDI Output device.
    ///          It is the callers responsibility to ensure that the message is valid.
    void sendMidiMessageToMidiOutDevice(const std::string &deviceName, const uint8_t *midiData, int length);
    void sendMidiMessageToMidiOutDevice(const std::string &deviceName, std::string &midiData);
    void sendMidiMessageToMidiOutDevice(const std::string &deviceName, const GPMidiMessage &message);

    /// \brief   Convert ASCII text into a hex string, suitable for including in a SysEx message
    std::string textToHexString(const std::string &text);

    /// \brief   Insert a MIDI message into Gig Performer such that GP will respond to it as if it actually came from
    ///          the specified device. It is the caller's responsibility to ensure that the message is valid.
    void injectMidiMessageToMidiInputDevice(const std::string &deviceName, const uint8_t *midiData, int length);
    void injectMidiMessageToMidiInputDevice(const std::string &deviceName, std::string &midiData);

    /// \brief   Insert a MIDI message into Gig Performer such that GP will respond to it as if it actually came from
    ///          the specified Rig Manager global name/alias. It is the caller's responsibility to ensure that the
    ///          message is valid.
    void injectMidiMessageToMidiInputAlias(const std::string &rigManagerAlias, const uint8_t *midiData, int length);
    void injectMidiMessageToMidiInputAlias(const std::string &rigManagerAlias, std::string &midiData);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Rackspaces and Songs

    /// \brief   Query GP for the list of songs currently available.
    int getSongCount();

    /// \brief   Query GP for the name of a song at the given index (zero-based).
    std::string getSongName(int atIndex);

    /// \brief   Query GP for the name of a song artist at the given index (zero-based).
    std::string getArtistName(int atIndex);

    /// \brief   Get the full path to a ChordPro file associated with the song at the given index of the currently
    ///          active setlist.
    std::string getChordProFilenameForSong(int atIndex);

    /// \brief   Query GP for the index of the currently selected song.
    int getCurrentSongIndex();

    /// \brief   Get the uuid for the song at the given index.
    std::string getSongUuid(int atIndex);

    /// \brief   Query GP for the name of the variation associated with the song and song part with the given
    ///          (zero-based) indices.
    std::string getVariationNameForSongPart(int atSongIndex, int atPartIndex);

    /// \brief   Query GP for the number of song parts in the song at the given index.
    int getSongpartCount(int atSongIndex);

    /// \brief   Query GP for the name of the song part at the specified (zero-based) index of the specified song.
    std::string getSongpartName(int atSongIndex, int atPartIndex);

    /// \brief   Query GP for the index of the currently selected song part index.
    int getCurrentSongpartIndex();

    /// \brief   Tell GP to switch to the song and song part with the given (zero-based) indices.
    bool switchToSong(int songIndex, int partIndex);

    /// \brief   Tell GP to switch to the song part with the given (zero-based) index in the current song.
    bool switchToSongPart(int partIndex);

    /// \brief   Returns the number of setlists in the currently gig file.
    int getSetlistCount();

    /// \brief   Gets the name of the setlist at the given index.
    std::string getSetlistName(int setlistIndex);

    /// \brief   Returns the index of the current setlist.
    int getCurrentSetlistIndex();

    /// \brief   Switch to the setlist defined by the index.
    /// \return  True if Gig Performer has successfully switched to the given setlist.
    bool switchToSetlist(int setlistIndex);

    /// \brief   Returns the number of rackspaces in the gig file.
    int getRackspaceCount();

    /// \brief   Get the name of rackspace atIndex.
    std::string getRackspaceName(int atIndex);

    /// \brief   Get the rackspace currently in use.
    int getCurrentRackspaceIndex();

    /// \brief   Get the uuid for the rackspace at the given index.
    std::string getRackspaceUuid(int atIndex);

    /// \brief   Get the rackspace currently in use.
    int getCurrentVariationIndex();

    /// \brief   Get the number of variations in the given rackspace.
    int getVariationCount(int atRackspaceIndex);

    /// \brief   Get the name of a specific variation at the given rackspace index.
    std::string getVariationName(int atRackspaceIndex, int atIndex);

    /// \brief   Switch to the given rackspace and variation.
    /// \return  true if successful, false else
    bool switchToRackspace(int rackspaceIndex, int variationIndex = 0);

    /// \brief   Switch to the named rackspace and variation.
    /// \return  true if successful, false else
    bool switchToRackspaceName(const std::string &rackspace, const std::string &variation = "");

    /// \brief   Switch to the variation.
    /// \return  true if successful, false else
    bool switchToVariation(int variationIndex = 0);

    /// \brief   Move to previous variation or rackspace.
    void previous();

    /// \brief   Move to next variation or rackspace.
    void next();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Interacting with plugins

    /// \brief   Get a list of all plugins defined (i.e, with handles) in the currently active rackspace or in the
    ///          global rackspace.
    void getPluginList(std::vector<std::string> &list, bool useGlobalRackspace);

    /// \brief   Indicates whether the plugin with the given handle exists in the currently active rackspace or in the
    ///          global rackspace.
    bool pluginExists(const std::string &pluginHandle, bool useGlobalRackspace);

    /// \brief   Set a parameter value for a plugin with the given handle in the currently active rackspace or in the
    ///          global rackspace.
    void setPluginParameter(const std::string &pluginHandle, int parameterNumber, double value,
                            bool useGlobalRackspace);

    /// \brief   Returns the value of the given parameter in the plugin with the given handle in the currently active
    ///          rackspace or in the global rackspace.
    double getPluginParameter(const std::string &pluginHandle, int parameterNumber, bool useGlobalRackspace);

    /// \brief   Returns the number of parameters exposed by the plugin with the given handle in the currently active
    ///          rackspace or in the global rackspace.
    int getPluginParameterCount(const std::string &pluginHandle, bool useGlobalRackspace);

    /// \brief   Returns the name of the parameter at the specified parameter number of the plugin with the given handle
    ///          in the currently active rackspace or in the global rackspace.
    std::string getPluginParameterName(const std::string &pluginHandle, int parameterIndex, bool useGlobalRackspace);

    /// \brief   Returns the current text value of the parameter at the specified parameter number of the plugin with
    ///          the given handle in the currently active rackspace or in the global rackspace.
    std::string getPluginParameterText(const std::string &pluginHandle, int parameterIndex, bool useGlobalRackspace);
    
    /// \brief   Returns the user-defined caption name of the plugin with
    ///          the given handle in the currently active rackspace or in the global rackspace.
    std::string getPluginCaption(const std::string &pluginHandle, bool useGlobalRackspace);
    
    /// \brief   Returns the vendor-defined name of the plugin with
    ///          the given handle in the currently active rackspace or in the global rackspace.
    std::string getPluginName(const std::string &pluginHandle, bool useGlobalRackspace);
   
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Interacting with gig files

    /// \brief   Try to save the file (normally overwriting the existing one). However, if withTimestamp is true, then
    ///          create a subfolder with the same name as the gigfile and save the current file in it, appending the
    ///          current time to it.
    /// \warning Time Stamp not yet implemented
    bool saveGigUnconditionally(bool withTimestamp);

    /// \brief   Look for a gigfile in a special folder (TBD) that has the prefix indexNumber and try to load it.
    /// \warning Not yet implemented.
    bool loadGigByIndex(int indexNumber);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Miscellaneous

    /// \brief   Get the global playhead state
    bool getPlayheadState();

    /// \brief   Enable or disable the global playhead.
    void setPlayheadState(bool play);

    /// \brief   Same as clicking the global "Tap Tempo" button.
    void tap();

    /// \brief   Stop all notes in the current rackspace.
    void panic();

    /// \brief   Set the global tempo in Gig Performer.
    void setBPM(double bpm);

    /// \brief   Get the global tempo in Gig Performer.
    double getBPM();

    /// \brief   Get the current time signature in Gig Performer.
    void getCurrentTimeSignature(int &numerator, int &denominator);

    /// \brief   Send the message to the console output (works only when Xcode is open).
    void consoleLog(const char *message);
    void consoleLog(const std::string &message);

    /// \brief   Display the message in the Script Logger window, possibly opening the window if it is not already open.
    void scriptLog(const char *message, bool openLogWindow);
    void scriptLog(const std::string &message, bool openLogWindow);

    /// \brief   Returns the GP instance name
    std::string getInstanceName();

    /// \brief   Returns the folder path where your library is installed.
    /// \details This is useful when you need to access other resource files installed in the same or a relative
    ///          location to the library.
    std::string getPathToMe();

  private:
    LibraryHandle fHandle;
};

} // namespace sdk
} // namespace gigperformer
