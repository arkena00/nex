########################################################
#####################  PLATFORM  #######################
########################################################
if(WIN32)
    set(NK_OS_NAME "windows")
    set(NXS_OS_DEFINE_LIST -DNXS_WIN -DNDB_WIN
            -DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB
            -D_WIN32_WINDOWS=0x0501 -D_WINSOCK_DEPRECATED_NO_WARNINGS)
    list(APPEND NXS_LIB_LIST user32 wsock32 ws2_32)
    if(MSVC)
        list(APPEND NXS_LIB_LIST
                boost_system-vc140-mt-1_63
                boost_filesystem-vc140-mt-1_63
                boost_serialization-vc140-mt-1_63)
    endif()
endif()

if(UNIX)
    set(NK_OS_NAME "linux")
    set(NXS_OS_DEFINE_LIST -DNXS_UNIX -DNDB_UNIX)
    find_package(Boost COMPONENTS system filesystem serialization REQUIRED)
    list(APPEND NXS_LIB_LIST ${Boost_LIBRARIES} pthread dl)
endif()

########################################################
#####################  COMPILER  #######################
########################################################
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
set(CMAKE_BUILD_TYPE release)

########################################################
#######################  PATH  #########################
########################################################
set(NK_CMAKE_BINARY_PATH cmake/${CMAKE_BUILD_TYPE})
set(NXS_BINARY_PATH ${CMAKE_CURRENT_LIST_DIR}/${NK_CMAKE_BINARY_PATH})

set(NK_PATH "${CMAKE_CURRENT_LIST_DIR}/../../")
set(NEX_PATH ${NK_PATH}/nex)
set(EXTLIB_PATH ${NEX_PATH}/extlib)

########################################################
#####################  INCLUDE  ########################
########################################################
set(INCLUDE_LIST
        ${NEX_PATH}/system/include
        ${EXTLIB_PATH}/boost/include
        ${EXTLIB_PATH}/stdz/include
        ${NK_PATH}/nds/include
        ${NK_PATH}/ndb/include)
include_directories(${INCLUDE_LIST})

link_directories(${EXTLIB_PATH}/boost/lib/)
link_directories(${NEX_PATH}/server/desktop/lib)

add_definitions(${NXS_OS_DEFINE_LIST} -DNDB_ENGINE_SQL)
