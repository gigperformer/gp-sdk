# Changelog

# 46

- A new API for getting the instance name from a GigPerformer instance:
  - `GP_GetInstanceName` (C) and
  - `GigPerformerFunctions::getInstanceName` (C++)

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

- Initial publicly released version.
