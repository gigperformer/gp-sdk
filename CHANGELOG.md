# Changelog

# 46

- A new API for getting the text value of a plugin parameter:
  - `GP_GetPluginParameterText` (C) and `GigPerformerFunctions::getPluginParameterText` (C++).

- New APIs for enabling the metronome and checking its status:
  - `GP_EnableMetronome` (C) and `GigPerformerFunctions::enableMetronome` (C++).
  - `GP_MetronomeEnabled` (C) and `GigPerformerFunctions::metronomeEnabled` (C++).

- A new API for getting the variation name associated with a specified song and song part:
  - `GP_GetVariationNameForSongPart` (C) and `GigPerformerFunctions::getVariationNameForSongPart` (C++).

- A new API for getting the ChordPro filepath to the currently active song:
  - `GP_GetChordProFilenameForSong` (C) and `GigPerformerFunctions::getChordProFilenameForSong` (C++).

- Several new APIs concerning set lists:
  - `GP_GetSetlistCount()` (C) and `GigPerformerFunctions::getSetlistCount()` (C++)
  - `GP_GetSetlistName()` (C) and `GigPerformerFunctions::getSetlistName()` (C++)
  - `GP_GetCurrentSetlistIndex()` (C) and `GigPerformerFunctions::getCurrentSetlistIndex()` (C++)
  - `GP_SwitchToSetlist()` (C) and `GigPerformerFunctions::switchToSetlist(int setlistIndex)` (C++)

# 44

- Initial publicly released version.
