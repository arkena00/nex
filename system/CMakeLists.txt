cmake_minimum_required(VERSION 3.1)

project(nxs)

include(nxs.cmake)

########################################################
######################  TARGET  ########################
########################################################
file(GLOB_RECURSE SOURCE_LIST "source/*.cpp")
file(GLOB_RECURSE NDB_SOURCE_LIST "${NK_PATH}/ndb/source/ndb/*.cpp"  "${NK_PATH}/ndb/source/ndb/*.c")

# binary
# add_library(nxs SHARED ${SOURCE_LIST} ${NDB_SOURCE_LIST})
add_library(nxs_object OBJECT ${SOURCE_LIST} ${NDB_SOURCE_LIST})
