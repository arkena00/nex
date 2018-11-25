cmake_minimum_required(VERSION 3.1)

project(nxi)

message("--------------------------------------------------------
                         NXI
--------------------------------------------------------")

# functions
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

# module_add
macro(module_add name)
    add_library(module_${name} INTERFACE)
    target_include_directories(module_${name} INTERFACE ${MODULE_ROOT}/${name})
    set(MODULE_LIST ${MODULE_LIST} "module_${name};" PARENT_SCOPE)
endmacro()

# module_load
macro(module_build name)
    set(NXI_MODULE_${name} ON)
endmacro()

# module_source
macro(module_source)
    foreach (SRC ${ARGN})
        list (APPEND MODULE_SOURCE_LIST "${MODULE_ROOT}/${MODULE_CURRENT}/${SRC}")
    endforeach()
    target_sources(module_${MODULE_CURRENT} INTERFACE ${MODULE_SOURCE_LIST})
endmacro()


# user config file
include(user-config.cmake OPTIONAL)

# must be set before files scan
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCE_LIST "source/*.cpp" "source/*.qrc" "include/*.hpp")

########################################################
######################   Modules  ######################
########################################################
message("Module build")
set(MODULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/experimental/module")

SUBDIRLIST(SUBDIRS ${MODULE_ROOT})

# add modules
foreach(module ${SUBDIRS})
    option(NXI_MODULE_${module} "Module ${module}" ${NXI_MODULE_${module}})
    message("- ${module} : ${NXI_MODULE_${module}}")
    if (NXI_MODULE_${module})
        set(MODULE_CURRENT ${module})
        add_subdirectory(${MODULE_ROOT}/${module})
        # create variables for generated file
        string(APPEND  NXI_MODULE_STATIC_INCLUDE "#include \"experimental/module/${module}/${module}.hpp\"\n")
        string(APPEND  NXI_MODULE_STATIC_INIT ", ${module}_{ nxi_core }\n")
        string(APPEND  NXI_MODULE_STATIC_LOAD "${module}_.load();\n")
        string(APPEND  NXI_MODULE_STATIC_MEMBER "nxi::modules::${module} ${module}_;\n")
    endif()
endforeach()

# create container file
configure_file(
        "${MODULE_ROOT}/static_module.hpp.in"
        "${MODULE_ROOT}/static_module.hpp"
)


########################################################
#######################   Bin  #########################
########################################################
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui WebEngine WebEngineWidgets)


add_executable(nxi ${SOURCE_LIST})
target_include_directories(nxi PUBLIC include)
target_link_libraries(nxi lib_nxs ${MODULE_LIST})


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