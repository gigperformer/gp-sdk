add_library(gigperformer_sdk_c INTERFACE)
add_library(gigperformer::sdk::c ALIAS gigperformer_sdk_c)
target_sources(
  gigperformer_sdk_c
  INTERFACE
    # Headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/c/GPTypes.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/c/exports.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/c/imports.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/c/macros.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/c/utils.h>
    # Sources
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/c/imports.c>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/c/utils.c>)
target_include_directories(gigperformer_sdk_c
                           INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
