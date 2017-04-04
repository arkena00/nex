cmake_minimum_required(VERSION 3.1)

project(nxs)

include(nxs.cmake)

########################################################
######################  TARGET  ########################
########################################################
file(GLOB_RECURSE NXS_FILE_LIST "source/*.cpp" "include/*.hpp" "include/*.tcc")
file(GLOB_RECURSE NDB_FILE_LIST "${NK_PATH}/ndb/source/ndb/*.cpp"  "${NK_PATH}/ndb/source/ndb/*.c")

# binary
# add_library(nxs SHARED ${SOURCE_LIST} ${NDB_SOURCE_LIST})
add_library(nxs_object OBJECT ${NXS_FILE_LIST} ${NDB_FILE_LIST})
