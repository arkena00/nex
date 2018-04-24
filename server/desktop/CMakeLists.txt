cmake_minimum_required(VERSION 3.1)

project(server)

add_executable(server source/main.cpp)

target_link_libraries(server lib_nxs)

set_target_properties(server
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${NEX_BIN_ROOT}"
        OUTPUT_NAME  "nex_server"
        )