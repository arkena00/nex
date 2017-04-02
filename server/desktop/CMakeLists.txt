cmake_minimum_required(VERSION 3.1)

project(server)

include(../../system/nxs.cmake)

add_subdirectory(../../system ${NXS_BINARY_PATH})

add_executable(server source/main.cpp $<TARGET_OBJECTS:nxs_object>)

set_target_properties(server
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${NK_OS_NAME}"
        OUTPUT_NAME  "nex"
        )