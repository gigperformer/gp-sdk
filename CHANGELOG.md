# Changelog

# 46

Extensions built with this SDK will be **compatible to Gig Performer 4.7**.

## Breaking changes
- The `OnGlobalPlayStateChanged` callback will now tell you whether the user initiated playing via Gig Performer directly or Ableton Link.
  Thus, the `playing` parameter changed from `bool` to `double` (see the function's documentation for more details).

## New APIs

- New APIs for getting the plugin caption and plugin name:
  - `GP_GetPluginCaption` (C) and `GigPerformerFunctions::getPluginCaption` (C++)
  - `GP_GetPluginName` (C) and `GigPerformerFunctions::getPluginName` (C++)

- A new API for getting the artist name for a song:
  - `GP_GetArtistName` (C) and `GigPerformerFunctions::getArtistName` (C++)

- A new API for getting the global time signature:
  - `GP_GetCurrentTimeSignature` (C) and `GigPerformerFunctions::getCurrentTimeSignature` (C++)

- A new API to trigger Gig Performer's Panic mode (e.g. to send MIDI note off messages or reset the audio engine):
  - `GP_Panic` (C) and `GigPerformerFunctions::panic` (C++)

- New APIs for getting and setting the widget bounds:
  - `GP_GetWidgetBounds` (C) and `GigPerformerFunctions::getWidgetBounds` (C++)
  - `GP_SetWidgetBounds` (C) and `GigPerformerFunctions::setWidgetBounds` (C++)

- New APIs for getting and setting the hide state of a widget:
  - `GP_GetWidgetHideState` (C) and `GigPerformerFunctions::getWidgetHideState` (C++)
  - `GP_SetWidgetHideOnPresentation` (C) and `GigPerformerFunctions::setWidgetHideOnPresentation` (C++)

- A new API for getting the instance name from a Gig Performer instance:
  - `GP_GetInstanceName` (C) and `GigPerformerFunctions::getInstanceName` (C++)

- A new API for mapping a widget to a plugin parameter:
  - `GP_MapWidgetToPluginParameter` (C) and `GigPerformerFunctions::mapWidgetToPluginParameter` (C++)

- New APIs for getting the rackspace and song universally unique identifier (UUID):
  - `GP_GetRackspaceUuid` (C) and `GigPerformerFunctions::getRackspaceUuid` (C++)
  - `GP_GetSongUuid` (C) and `GigPerformerFunctions::getSongUuid` (C++)

- A new API for getting the text value of a plugin parameter:
  - `GP_GetPluginParameterText` (C) and `GigPerformerFunctions::getPluginParameterText` (C++)

- New APIs for enabling the metronome and checking its status:
  - `GP_EnableMetronome` (C) and `GigPerformerFunctions::enableMetronome` (C++)
  - `GP_MetronomeEnabled` (C) and `GigPerformerFunctions::metronomeEnabled` (C++)

- A new API for getting the variation name associated with a specified song and song part:
  - `GP_GetVariationNameForSongPart` (C) and `GigPerformerFunctions::getVariationNameForSongPart` (C++)

- A new API for getting the ChordPro filepath to the currently active song:
  - `GP_GetChordProFilenameForSong` (C) and `GigPerformerFunctions::getChordProFilenameForSong` (C++)

- Several new APIs concerning setlists:
  - `GP_GetSetlistCount()` (C) and `GigPerformerFunctions::getSetlistCount()` (C++)
  - `GP_GetSetlistName()` (C) and `GigPerformerFunctions::getSetlistName()` (C++)
  - `GP_GetCurrentSetlistIndex()` (C) and `GigPerformerFunctions::getCurrentSetlistIndex()` (C++)
  - `GP_SwitchToSetlist()` (C) and `GigPerformerFunctions::switchToSetlist(int setlistIndex)` (C++)

# 44

Extensions built with this SDK will be **compatible to Gig Performer 4.5.8**.

- Initial publicly released version.
