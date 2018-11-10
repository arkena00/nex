cmake_minimum_required(VERSION 3.7)

project(nex C CXX)

message("--------------------------------------------------------
                         NEX
--------------------------------------------------------")

# root
set(NEX_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(NEX_BIN_ROOT ${NEX_ROOT}/bin)
set(THIRD_PARTY_ROOT ${NEX_ROOT}/third_party)


#-------------------------------------------------------
#                      COMPILER
#-------------------------------------------------------
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#-------------------------------------------------------
#                      SUBPROJECT
#-------------------------------------------------------

# system (nxs)
add_subdirectory(system)

# server
add_subdirectory(server/desktop)

# client
add_subdirectory(client/nxi)