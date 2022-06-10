/// \file    GigPerformerAPI.h
/// \brief   Contains the definitions of the GigPerformerAPI class.

#pragma once

#include <string>
#include <vector>

#include "gigperformer/sdk/GigPerformerFunctions.h"

namespace gigperformer
{
namespace sdk
{

/// \brief   Base class for extension implementations.
class GigPerformerAPI : public GigPerformerFunctions
{
  public:
    /// \brief   Use this to register callbacks and to do any other setup you need.
    virtual void Initialization();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Mandatory functions
    /// \details You must implement these.

    /// \brief   Get information about this extension
    /// \details This is the first thing called by Gig Performer. It is expecting back a short XML file with information
    ///          specified as below. This information will be presented to the user who can decide whether this
    ///          particular library should be used.
    ///
    ///              <Library>
    ///                  <Product name="My ControlSurface" Version="1.0" BuildDate="12/1/2019"></Product>
    ///                  <Description>This product does blah blah blah</Description>
    ///                  <ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>
    ///              </Library>
    virtual std::string GetProductDescription() = 0;

  public:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    GPScript
    /// \details Extensions may provide functions which can be called from GPScript. For that purpose, the functions in
    ///          this section can be used.

    /// \brief   Called by Gig Performer during startup to get a list of GPScript functions implemented by the
    ///          extension.
    /// \details This function may be called multiple times, especially for different values of \p location.
    /// \param   location indicates which kind of script entity is asking for the functions.
    /// \param   list *list is set to the start of a buffer buffer containing elements of type
    ///               \ref ExternalAPI_GPScriptFunctionDefinition.
    /// \return  Number of elements in \p list.
    virtual int RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                                     ExternalAPI_GPScriptFunctionDefinition **list);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Callbacks
    /// \details Only implement the callbacks in which you are interested

    /// \brief   Called when a MIDI event arrives from a device for which the library has registered its interest in
    ///          listening.
    /// \return  True if the MIDI event should be passed on to the next handler
    virtual bool OnMidiIn(const std::string &deviceName, const uint8_t *data, int length);

    /// \brief   Called when user enters or exits editing mode.
    virtual void OnEditStateChanged(bool inEditState);

    /// \brief   Called when the user switches into the diagram/connection mode
    virtual void OnSwitchToWiringView();

    /// \brief   Called when the user switches into rackspace mode
    virtual void OnSwitchToPanelView();

    /// \brief   Called when the global tempo is changed.
    /// \param   newBPM the new tempo (in beats per minute)
    virtual void OnTempoChanged(double newBPM);

    /// \brief   Called when the user switches into or out of setlist mode.
    /// \param   mode can be interpreted as GP_Mode
    virtual void OnModeChanged(int mode);

    /// \brief   Called when something in GP changes that can trigger a notification to the external API loaded.
    virtual void OnStatusChanged(GPStatusType status);

    /// \brief   Called when a MIDI device is connected or disconnected from the computer.
    /// \details You get an array of strings for the MIDI in and MIDI out device list respectively.
    virtual void OnMidiDeviceListChanged(std::vector<std::string> &inputs, std::vector<std::string> &outputs);

    /// \brief   Called when Gig Performer has finished initializing itself.
    virtual void OnOpen();

    /// \brief   Called when Gig Performer is about to shut down.
    virtual void OnClose();

    /// \brief   Called when user switches to a new rackspace.
    virtual void OnRackspaceActivated();

    /// \brief   Called when user switches to a new song in setlist mode.
    virtual void OnSongChanged(int oldIndex, int newIndex);

    /// \brief   Called when user switches to a new song part within the current song in setlist mode.
    virtual void OnSongPartChanged(int oldIndex, int newIndex);

    /// \brief   Called when the user changes the setlist.
    virtual void OnSetlistChanged(const std::string &newSetlistName);

    /// \brief   Called when user switches from one variation to another.
    virtual void OnVariationChanged(int oldIndex, int newIndex);

    /// \brief   Called when a widget is turned or otherwise adjusted.
    /// \details The library must register its interest in listening for such changes.
    virtual void OnWidgetValueChanged(const std::string &widgetName, double newValue);

    /// \brief   Called when a widget is created or destroyed.
    /// \details The library must register its interest in listening for such changes.
    /// \param   newState 0 if a widget was created, 1 if it was destroyed
    virtual void OnWidgetStateChanged(const std::string &widgetName, int newState);

    /// \brief   Called when a widget caption changes.
    /// \details The library must register its interest in listening for such changes.
    virtual void OnWidgetCaptionChanged(const std::string &widgetName, const std::string &newCaption);

    /// \brief   Called when the global play state changes
    /// \param   playing true if playing, false if stopped
    virtual void OnGlobalPlayStateChanged(bool playing);

    /// \brief   Called when the user switches in or out of tuner mode.
    virtual void OnTunerModeChanged(bool visible);

  public:
    // Functions that Gig Performer needs to be able to call in your library -
    // override as appropriate

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Panel support
    /// \details These are for inserting panels into a Gig Performer rackspace

    /// \brief   Returns how many panels your library provides
    virtual int GetPanelCount();

    /// \brief   Return the name of the panel at this index
    /// \param   index 0 <= index <= (panelCount - 1)
    virtual std::string GetPanelName(int index);

    /// \brief   Return the XML representation of a panel.
    virtual std::string GetPanelXML(int index);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Menu support
    /// \details These are for creating menu items in Gig Performer that can be used to trigger external functions
    ///          provided by the extension

    /// \brief   Return the number of menu items available.
    virtual int GetMenuCount();

    /// \brief   Return the name of menu item at index.
    virtual std::string GetMenuName(int index);

    /// \brief   Invoke the action associated with menu item at index.
    virtual void InvokeMenu(int itemIndex);

  public:
    explicit GigPerformerAPI(LibraryHandle handle);
    ~GigPerformerAPI() override;
};

/// Create an instance of the user-defined class that implements GigPerformerAPI.
/// Must be implemented by the library user.
/// \param handle may be nullptr. If so, callbacks cannot be created.
/// \return Pointer to a GigPerformerAPI implementation, created by new. The caller takes ownership of it.
GigPerformerAPI *CreateGPExtension(LibraryHandle handle);

} // namespace sdk
} // namespace gigperformer
