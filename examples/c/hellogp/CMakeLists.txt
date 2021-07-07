# CMakeLists.txt

# Always set the cmake min version.
cmake_minimum_required(VERSION 3.0)

set(GP_SDK_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../../sdk")
set(PROJECT_VERSION "1.0")
set(PROJECT_NAME "HelloGP-C")

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS
# to TRUE. See also:
# https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")

# Set the variable PROJ_NAME to whatever your library's name is, PROJECT_VERSION
# should be a version string like "0.1"
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

# Create our library target
add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

target_sources(
  ${PROJECT_NAME}
  PUBLIC ${GP_SDK_ROOT}/gigperformer/sdk/c/imports.c
  PUBLIC ${GP_SDK_ROOT}/gigperformer/sdk/c/utils.c)

include_directories(${GP_SDK_ROOT}) # So that the interface files can be found

# This will name your output .so files "libsomething.1.0" which is pretty useful
# set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION}
# SOVERSION ${PROJECT_VERSION} )

# Let's set compiler-specific flags
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  # G++
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  # MSVC
  target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W2 /c)
  # Set the DLLEXPORT variable to export symbols
  target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
endif()
