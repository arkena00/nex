cmake_minimum_required(VERSION 3.1)

project(nex)

# os specific
if(WIN32)
    set(OS_DEFINE_LIST NXS_WIN NDB_WIN)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile;" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_BUILD_TYPE Release )


################################################## PATH
# include path
set(INCLUDE_LIST
        ../extlib/boost/include
        ../../nds/include
        ../../ndb/include
        module/nxs/include)
include_directories(${INCLUDE_LIST})

# lib path
link_directories(module/nxs/lib ../extlib/boost/lib/)


# binary
add_executable(${PROJECT_NAME} "source/desktop/main.cpp")

# define
target_compile_definitions(${PROJECT_NAME} PUBLIC ${OS_DEFINE_LIST} NDB_ENGINE_SQL)

# lib
set(LIB_LIST
        nxs
        user32
        wsock32
        ws2_32
        boost_system-mgw62-mt-s-1_63
        boost_filesystem-mgw62-mt-s-1_63
        boost_serialization-mgw62-mt-s-1_63)
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        OUTPUT_NAME  "nex"
        )

# post build
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/bin/nex.exe
        ${CMAKE_CURRENT_SOURCE_DIR}/build/win32/nex.exe)