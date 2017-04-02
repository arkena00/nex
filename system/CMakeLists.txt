cmake_minimum_required(VERSION 3.1)

project(nxs)

#########################################################
######################  PLATFORM  #######################
#########################################################
if(WIN32)
    set(OS_NAME "windows")
    set(OS_DEFINE_LIST NXS_WIN NDB_WIN BOOST_DATE_TIME_NO_LIB BOOST_REGEX_NO_LIB _WIN32_WINDOWS=0x0501)
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

########################################################
#######################  PATH  #########################
########################################################
set(NK_PATH "../../")
set(NEX_PATH ${NK_PATH}/nex)
set(EXTLIB_PATH ${NEX_PATH}/extlib)
# set(NEX_BUILD_PATH "${CMAKE_CURRENT_SOURCE_DIR}../../../build/${OS_NAME}")

########################################################
#####################  COMPILER  #######################
########################################################
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_BUILD_TYPE Release )

set(NXS_DEFINE_LIST {$OS_DEFINE_LIST} NDB_ENGINE_SQL)

########################################################
#####################  INCLUDE  ########################
########################################################
set(INCLUDE_LIST
        include
        ${EXTLIB_PATH}/boost/include
        ${NK_PATH}/nds/include
        ${NK_PATH}/ndb/include)
include_directories(${INCLUDE_LIST})

# lib path
link_directories(${EXTLIB_PATH}/boost/lib/)

########################################################
######################  TARGET  ########################
########################################################
file(GLOB_RECURSE SOURCE_LIST "source/*.cpp")
file(GLOB_RECURSE NDB_SOURCE_LIST "${NK_PATH}/ndb/source/ndb/*.cpp"  "${NK_PATH}/ndb/source/ndb/*.c")

# binary
add_library(nxs SHARED ${SOURCE_LIST} ${NDB_SOURCE_LIST})
add_library(nxs_object OBJECT ${SOURCE_LIST} ${NDB_SOURCE_LIST})

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
