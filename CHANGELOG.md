# Changelog

# 46

- A new API for getting the ChordPro filepath to the currently active song:
  - `GP_GetChordProFilenameForSong` (C) and `GigPerformerFunctions::getChordProFilenameForSong` (C++).
- Several new APIs concerning set lists:
  - `GP_GetSetlistCount()` (C) and `GigPerformerFunctions::getSetlistCount()` (C++)
  - `GP_GetSetlistName()` (C) and `GigPerformerFunctions::getSetlistName()` (C++)
  - `GP_GetCurrentSetlistIndex()` (C) and `GigPerformerFunctions::getCurrentSetlistIndex()` (C++)
  - `GP_SwitchToSetlist()` (C) and `GigPerformerFunctions::switchToSetlist(int setlistIndex)` (C++)

# 44

- Initial publicly released version.
