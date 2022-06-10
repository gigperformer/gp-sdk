/// \file    exports.h
/// \brief   Declares functions which must be implemented by the extension.

#pragma once

#include "gigperformer/sdk/macros.h"
#include "gigperformer/sdk/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /// \brief   This function is implemented by the SDK itself.
    /// \warning Do not define this function yourself.
    EXPORTED int GPGetSDKVersion();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Mandatory functions
    /// \details You must implement these in your extension library.

    /// \brief   Get information about this extension
    /// \details GPQuery, which MUST be implemented by the library is the first thing called by
    ///          Gig Performer. It is expecting back a short XML file with information specified
    ///          as below. This information will be presented to the user who can decide whether this particular library
    ///          should be used.
    ///
    ///              <Library>
    ///                  <Product name="My ControlSurface" Version="1.0" BuildDate="12/1/2019"></Product>
    ///                  <Description>This product does blah blah blah</Description>
    ///                  <ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>
    ///              </Library>
    EXPORTED void GPQueryLibrary(char *xmlInfoBuffer, int bufferLength);

    /// \brief   If the user decides that this library should be used then it will call GPRegister.
    /// \details It passes in the address of a function that the library developer can call to request the address of
    ///          other functions that Gig Performer makes available to the developer. The handle that is passed in
    ///          must be saved and all GP function calls that are used by the library will pass in that handle as the
    ///          first parameter The XML buffer is used to let the library developer provide multiple items of interest.
    EXPORTED void GPRegister(TGetGPFunctionType getGPFunctionAddress, LibraryHandle handle);

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
    EXPORTED int RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                                      ExternalAPI_GPScriptFunctionDefinition **list);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Panel support
    /// \details If your library includes resources such as predefined front panels, you will need to implement the
    ///          following three functions so that Gig Performer can query your library to get access to the panels that
    ///          are available through your library. If you are working in C++, make sure you enclose these functions
    ///          with `extern "C"` so as to ensure the appropriate calling conventions are used.

    /// \brief   Return the number of panels available from this library
    EXPORTED int GetPanelCount();

    /// \brief   Fill the buffer with the name of a panel at the specified index up to the maximum buffer size.
    /// \return  number of bytes that would be needed for the full panel name (including 0 terminator) and you can call
    ///          the function again with a larger buffer if necessary.
    EXPORTED int GetPanelName(int index, char *buffer, int bufferLength);

    /// \brief   Fill the buffer with a chunk of XML code representing a predefined panel.
    /// \details You can create these by saving a Gig Performer panel. The function returns the number of bytes that
    ///          would be needed for the full panel name and you can call the function again with a larger buffer if
    ///          necessary.
    EXPORTED int GetPanelXML(int index, char *buffer, int bufferLength);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Menu support
    /// \details Gig Performer allows your library to register menu items that a user can select to invoke functionality
    ///          implemented in your library. You will need to implement the following three functions for this feature
    ///          to work. If you are working in C++, make sure you enclose these functions with `extern "C"` so as to
    ///          ensure the appropriate calling conventions are used.

    /// \brief   Return the number of menu items available from this library
    EXPORTED int GetMenuCount();

    /// \brief   Fill the buffer with the name of a menu at the specified index up to the maximum buffer size.
    /// \details The function returns the number of bytes that would be needed for the full menu name and you can call
    ///          the function again with a larger buffer if necessary.
    EXPORTED int GetMenuName(int index, char *buffer, int bufferLength);

    /// \brief   Invokes the code in your library associated with the provided menu index.
    EXPORTED void InvokeMenu(int index);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \name    Callbacks
    /// \details Only implement the callbacks in which you are interested

    /// \brief   Called when a MIDI event arrives from a device for which the library has registered its interest in
    ///          listening.
    /// \return  True if the MIDI event should be passed on to the next handler
    EXPORTED bool OnMidiIn(const char *deviceName, const uint8_t *data, int length);

    /// \brief   Called when user enters or exits editing mode.
    EXPORTED void OnEditStateChanged(bool inEditState);

    /// \brief   Called when the user switches into the diagram/connection mode
    EXPORTED void OnSwitchToWiringView();

    /// \brief   Called when the global tempo is changed.
    EXPORTED void OnTempoChanged(double newBPM);

    /// \brief   Called when the user switches into rackspace mode
    EXPORTED void OnSwitchToPanelView();

    /// \brief   Called when the user switches into or out of setlist mode.
    /// \param   mode can be interpreted as GP_Mode
    EXPORTED void OnModeChanged(int mode);

    /// \brief   Called when something in GP changes that can trigger a notification to the external API loaded.
    EXPORTED void OnStatusChanged(GPStatusType status);

    /// \brief   Called when a MIDI device is connected or disconnected from the computer.
    /// \details You get an array of strings for the MIDI in and MIDI out device list respectively.
    EXPORTED void OnMidiDeviceListChanged(const char **inputs, int inputCount, const char **outputs, int outputCount);

    /// \brief   Called when Gig Performer has finished initializing itself.
    EXPORTED void OnOpen();

    /// \brief   Called when Gig Performer is about to shut down.
    EXPORTED void OnClose();

    /// \brief   Called when user switches to a new rackspace.
    EXPORTED void OnRackspaceActivated();

    /// \brief   Called when user switches to a new song in setlist mode.
    EXPORTED void OnSongChanged(int oldIndex, int newIndex);

    /// \brief   Called when user switches to a new song part within the current song in setlist mode.
    EXPORTED void OnSongPartChanged(int oldIndex, int newIndex);

    /// \brief   Called when the user changes the setlist.
    EXPORTED void OnSetlistChanged(const char *newSetlistName);

    /// \brief   Called when the user switches in or out of tuner mode.
    EXPORTED void OnTunerModeChanged(bool visible);

    /// \brief   Called when user switches from one variation to another.
    EXPORTED void OnVariationChanged(int oldIndex, int newIndex);

    /// \brief   Called when a widget is turned or otherwise adjusted.
    /// \details The library must register its interest in listening for such changes.
    EXPORTED void OnWidgetValueChanged(const char *widgetName, double newValue);

    /// \brief   Called when a widget is created or destroyed.
    /// \details The library must register its interest in listening for such changes.
    /// \param   newState 0 if a widget was created, 1 if it was destroyed
    EXPORTED void OnWidgetStateChanged(const char *widgetName, int newState);

    /// \brief   Called when a widget caption changes.
    /// \details The library must register its interest in listening for such changes.
    EXPORTED void OnWidgetCaptionChanged(const char *widgetName, const char *newCaption);

#ifdef __cplusplus
}
#endif
