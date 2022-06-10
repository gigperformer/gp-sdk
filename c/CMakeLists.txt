add_library(gigperformer_sdk_c INTERFACE)
add_library(gigperformer::sdk::c ALIAS gigperformer_sdk_c)
target_sources(
  gigperformer_sdk_c
  INTERFACE
    # Headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/macros.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/types.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/exports.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/imports.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/utils.h>
    # Sources
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/imports.c>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/utils.c>)
target_include_directories(gigperformer_sdk_c
                           INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
