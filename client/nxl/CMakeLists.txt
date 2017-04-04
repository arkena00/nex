cmake_minimum_required(VERSION 3.1)

project(nxl)

include(../../system/nxs.cmake)

add_subdirectory(../../system ${NXS_BINARY_PATH})

add_executable(nxl main.cpp $<TARGET_OBJECTS:nxs_object>)

target_link_libraries(nxl ${NXS_LIB_LIST})

set_target_properties(nxl
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        OUTPUT_NAME  "nxl"
        )