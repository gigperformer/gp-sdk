# CMakeLists.txt

#For OS X you need to define the following two entries
#The first one will depend on what SDKs are available on your system
#set(CMAKE_OSX_SYSROOT macosx10.15)
#set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")

#Note - depending on the version of Xcode that you are using, you might have to copy an SDK to the appropriate location
#Look in   /Library/Developer/CommandLineTools/SDKs for SDKs
#As of Xcode 10.12, the SDKs seems to need to live at /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs

# Always set the cmake min version.
cmake_minimum_required(VERSION 3.0)

# Set the GP_SDK_ROOT variable to the GP_SDK folder
set (GP_SDK_ROOT "../../..")
set (PROJECT_VERSION "1.0")
set (PROJECT_NAME "HelloGP-C")

# Set the variable PROJ_NAME to whatever your library's name is, PROJECT_VERSION should be a version string like "0.1"
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Create our library target
add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)


target_sources(${PROJECT_NAME}
  PUBLIC ${GP_SDK_ROOT}/interfaces/C/imports.c
  PUBLIC ${GP_SDK_ROOT}/interfaces/C/utils.c
)

include_directories(${GP_SDK_ROOT})                 # So that the interface files can be found

# This will name your output .so files "libsomething.1.0" which is pretty useful
#set_target_properties(${PROJECT_NAME}
#PROPERTIES
#    VERSION ${PROJECT_VERSION}
#    SOVERSION ${PROJECT_VERSION}
#)

# Let's set compiler-specific flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G++
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
endif()
