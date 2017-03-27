cmake_minimum_required(VERSION 3.1)

project(nxs)

#########################################################
#######################  OS SPEC  #######################
#########################################################
if(WIN32)
    set(OS_NAME "windows")
    set(OS_DEFINE_LIST NXS_WIN NDB_WIN BOOST_DATE_TIME_NO_LIB BOOST_REGEX_NO_LIB)
    list(APPEND LIB_LIST user32 wsock32 ws2_32)
    if(MSVC)
        list(APPEND LIB_LIST
                boost_system-vc140-mt-1_63
                boost_filesystem-vc140-mt-1_63
                boost_serialization-vc140-mt-1_63)
    endif()
endif()

if(UNIX)
    set(OS_NAME "linux")
    set(OS_DEFINE_LIST NXS_UNIX NDB_UNIX)
endif()

set(NEX_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}../../../build/${OS_NAME}")

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_BUILD_TYPE Release )

########################################################
#######################  PATH  #########################
########################################################
set(INCLUDE_LIST
        ../../../extlib/boost/include
        include
        ../../../../nds/include
        ../../../../ndb/include)
include_directories(${INCLUDE_LIST})

# lib path
link_directories(../../../extlib/boost/lib/)

########################################################
######################  TARGET  ########################
########################################################
file(GLOB_RECURSE SOURCE_LIST "source/*.cpp")
file(GLOB_RECURSE NDB_SOURCE_LIST "../../../../ndb/source/ndb/*.cpp"  "../../../../ndb/source/ndb/*.c")

# binary
add_library(nxs SHARED ${SOURCE_LIST} ${NDB_SOURCE_LIST})

# define
target_compile_definitions(nxs PUBLIC ${OS_DEFINE_LIST} NDB_ENGINE_SQL)

# lib
target_link_libraries(nxs ${LIB_LIST})

set_target_properties(nxs
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        OUTPUT_NAME  "nxs"
        PREFIX ""
        )
