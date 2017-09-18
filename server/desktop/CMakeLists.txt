cmake_minimum_required(VERSION 3.1)

project(server)

include(../../system/nxs.cmake)

add_subdirectory(../../system ${NXS_BINARY_PATH})

add_executable(server source/main.cpp $<TARGET_OBJECTS:nxs_object>)

target_link_libraries(server ${NXS_LIB_LIST})

set_target_properties(server
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY "${NEX_PATH}/server/desktop/lib"
        OUTPUT_NAME  "nex"
        )