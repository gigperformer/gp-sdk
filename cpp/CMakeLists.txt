add_library(gigperformer_sdk_cpp INTERFACE)
add_library(gigperformer::sdk::cpp ALIAS gigperformer_sdk_cpp)
target_sources(
  gigperformer_sdk_cpp
  INTERFACE
    # Headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/GigPerformerAPI.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/GigPerformerFunctions.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/GPMidiMessages.h>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/gigperformer/sdk/GPUtils.h>
    # Sources
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/entry.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/GigPerformerAPI.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/GigPerformerFunctions.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/GPMidiMessages.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/gigperformer/sdk/GPUtils.cpp>
)
target_include_directories(gigperformer_sdk_cpp
                           INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(gigperformer_sdk_cpp INTERFACE gigperformer_sdk_c)
