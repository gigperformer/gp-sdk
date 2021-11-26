# Changelog

## Refactoring

### New features

-   Easier integration of the SDK for CMake-based extensions
-   Documentation of API functions using Doxygen
-   All SDK code is formatted using [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html).

### Breaking changes

-   The `macros.h` header is removed.
    -   The `SetlistMode` and `FrontBackMode` are replaced by the enum `GP_Mode` containing `GP_SetlistMode` and `GP_FrontBackMode`.
-   The C++ API now resides in the namespace `gigperformer::sdk`.
    -   Clients shall use the qualified names.
    -   Workaround: Include `using namespace gigperformer::sdk` into your code.
-   The headers similarily now reside under `gigperformer/sdk`.
    -   Example: Change `#include "GigPerformerAPI.h"` to `#include "gigperformer/sdk/GigPerformerAPI.h"`.
-   The extension main class ("LibMain") may now be arbitrarily named and defined in an arbitrary namespace and header.
    -   In turn, the user **must** implement the factory function `gigperformer::sdk::CreateGPExtension(LibraryHandle)`.
-   The examples now reside in a separate repository.
    -   They show an example integration of the SDK.
-   `ExternalAPI_GPStatus` is renamed to `GPStatus`.

## 4.0.53

### New features

-   Added `GP_SetPlayheadState()` (C) and `GigPerformerFunctions::setPlayheadState()` (C++)

## 4.0.47

Initial considered version
