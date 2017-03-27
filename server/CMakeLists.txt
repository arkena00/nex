cmake_minimum_required(VERSION 3.1)

project(nex)

#########################################################
#######################  OS SPEC  #######################
#########################################################
if(WIN32)
    set(OS_NAME windows)
    set(OS_DEFINE_LIST NXS_WIN NDB_WIN
            BOOST_DATE_TIME_NO_LIB BOOST_REGEX_NO_LIB)
    list(APPEND LIB_LIST user32 wsock32 ws2_32)
    if(MSVC)
        set(OS_COMPILER_FLAG "/EHsc /MT")
        list(APPEND LIB_LIST
                boost_system-vc140-mt-1_63
                boost_filesystem-vc140-mt-1_63
                boost_serialization-vc140-mt-1_63)
    endif()
endif()

if(UNIX)
    set(OS_NAME linux)
    set(OS_DEFINE_LIST NXS_UNIX NDB_UNIX)

endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release )
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS ${OS_COMPILER_FLAG})

set(NEX_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/${OS_NAME}")
set(NK_PATH "../../")


########################################################
#######################  PATH  #########################
########################################################
set(INCLUDE_LIST
        ../extlib/boost/include
        ${NK_PATH}/nds/include
        ${NK_PATH}/ndb/include
        module/nxs/include)
include_directories(${INCLUDE_LIST})

# lib path
link_directories(module/nxs/lib ../extlib/boost/lib/)


########################################################
######################  TARGET  ########################
########################################################
file(GLOB_RECURSE NXS_SOURCE_LIST "module/nxs/source/*.cpp")
file(GLOB_RECURSE NDB_SOURCE_LIST "${NK_PATH}/ndb/source/ndb/*.cpp"  "${NK_PATH}/ndb/source/ndb/*.c")
add_executable(nex ${NXS_SOURCE_LIST} ${NDB_SOURCE_LIST} "source/desktop/main.cpp")

# define
target_compile_definitions(nex PUBLIC
        ${OS_DEFINE_LIST}
        NDB_ENGINE_SQL)

# lib
target_link_libraries(nex ${LIB_LIST})

set_target_properties(nex
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${NEX_BUILD_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${NEX_BUILD_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${NEX_BUILD_DIR}"
        OUTPUT_NAME  "nex"
        )
