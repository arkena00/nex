cmake_minimum_required(VERSION 3.1)

project(nxi)

include(../../system/nxs.cmake)

include_directories(${EXTLIB_PATH}/nazara/include ${EXTLIB_PATH}/nazara/ndk/include ./include)

link_directories(${EXTLIB_PATH}/nazara/lib)

add_subdirectory(../../system ${NXS_BINARY_PATH})

########################################################
#######################   Qt  ##########################
########################################################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui WebEngine WebEngineWidgets)

file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "source/*.qrc" "include/*.hpp")

add_executable(nxi ${SOURCE_LIST} $<TARGET_OBJECTS:nxs_object>)

target_link_libraries(nxi ${NXS_LIB_LIST}
        Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WebEngine Qt5::WebEngineWidgets
        NazaraCore NazaraGraphics NazaraRenderer NazaraUtility NazaraPlatform NazaraSDK )

set_target_properties(nxi
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        OUTPUT_NAME  "nxi"
        )

########################################################
###################   VS Filters  ######################
########################################################

foreach(_source IN ITEMS ${SOURCE_LIST})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

