cmake_minimum_required(VERSION 3.1)

project(nxi)

message("--------------------------------------------------------
                         NXI
--------------------------------------------------------")

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

message("Module compilation")
set(MODULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/experimental/module")

SUBDIRLIST(SUBDIRS ${MODULE_ROOT})

FOREACH(module ${SUBDIRS})
    message("- ${module}")
    include(${MODULE_ROOT}/${module}/${module}.cmake)
ENDFOREACH()


# must be set before files scan
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "source/*.qrc" "include/*.hpp")

add_executable(nxi ${SOURCE_LIST} ${MODULE_SOURCE_LIST})

# user config config file
include(user-config.cmake OPTIONAL)

########################################################
#######################   Qt  ##########################
########################################################
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui WebEngine WebEngineWidgets)



target_include_directories(nxi PUBLIC include)
target_link_libraries(nxi lib_nxs)


target_link_libraries(nxi ${NXS_LIB_LIST}
        Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WebEngine Qt5::WebEngineWidgets
        )

set_target_properties(nxi
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${NEX_BIN_ROOT}/nxi"
        OUTPUT_NAME  "nxi"
        )


if (!WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    add_custom_command(TARGET nxi POST_BUILD
            COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:nxi>)
endif()


message("--------------------------------------------------------")