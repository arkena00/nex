cmake_minimum_required(VERSION 3.1)

project(nxi)

#########################################################
#######################  OS SPEC  #######################
#########################################################
if(WIN32)
    set(OS "windows")
    set(TARGET_EXT ".exe")
    set(OS_DEFINE_LIST NXS_WIN NDB_WIN
            BOOST_DATE_TIME_NO_LIB BOOST_REGEX_NO_LIB)
    list(APPEND LIB_LIST user32 wsock32 ws2_32)

    set(CMAKE_PREFIX_PATH "C:/Qt/5.9/msvc2015")
    if(MSVC)
        list(APPEND LIB_LIST
                boost_system-vc140-mt-1_63
                boost_filesystem-vc140-mt-1_63
                boost_serialization-vc140-mt-1_63)
    endif()
endif()

if(UNIX)
    set(OS "linux")
    set(OS_DEFINE_LIST NXS_UNIX NDB_UNIX)
    find_package(Boost 1.62 COMPONENTS system filesystem serialization REQUIRED)
    list(APPEND LIB_LIST ${Boost_LIBRARIES})
endif()

########################################################
#######################   Qt  ##########################
########################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui WebEngine WebEngineWidgets)

########################################################
#####################  COMPILER  #######################
########################################################
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_BUILD_TYPE Release )


########################################################
#######################  PATH  #########################
########################################################
set(INCLUDE_LIST
        ../../extlib/boost/include
        ../../extlib/nazara/include
        ../../extlib/nazara/ndk/include
        include
        ../../../nds/include
        ../../../ndb/include
        ../../server/module/nxs/include)
include_directories(${INCLUDE_LIST})

# lib path
link_directories(../../extlib/boost/lib ../../extlib/nazara/lib)

########################################################
######################  TARGET  ########################
########################################################
file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "source/*.qrc" "include/*.hpp")
file(GLOB_RECURSE NDB_SOURCE_LIST "../../../ndb/source/ndb/*.cpp"  "../../../ndb/source/ndb/*.c")
file(GLOB_RECURSE NXS_SOURCE_LIST "../../server/module/nxs/source/nxs/*.cpp")

add_executable(${PROJECT_NAME} ${NDB_SOURCE_LIST} ${NXS_SOURCE_LIST} ${SOURCE_LIST})

# define
target_compile_definitions(${PROJECT_NAME} PUBLIC
        ${OS_DEFINE_LIST}
        NDB_ENGINE_SQL)
       # BOOST_ERROR_CODE_HEADER_ONLY)

########################################################
######################   LINK   ########################
########################################################
target_link_libraries(${PROJECT_NAME} ${LIB_LIST} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WebEngine Qt5::WebEngineWidgets)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        OUTPUT_NAME  "nxi"
        )
