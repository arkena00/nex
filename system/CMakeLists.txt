cmake_minimum_required(VERSION 3.7)

project(nxs)

# root
set(NXS_ROOT ${NEX_ROOT}/system)

# files
file(GLOB_RECURSE NXS_FILES "source/*.cpp" "include/*.hpp" "include/*.tpp")

# nxs interface lib
add_library(lib_nxs INTERFACE)

target_sources(lib_nxs INTERFACE ${NXS_FILES})

# include
target_include_directories(lib_nxs INTERFACE
        ${NXS_ROOT}/include
        ${THIRD_PARTY_ROOT}/asio/asio/include
        ${THIRD_PARTY_ROOT}/cereal/include
        ${THIRD_PARTY_ROOT}/nds/include)

# define
if (WIN32)
    target_compile_options(lib_nxs INTERFACE /wd4996)
    target_compile_definitions(lib_nxs INTERFACE NXS_WIN _WIN32_WINNT=0x0501
            ASIO_STANDALONE
            BOOST_ERROR_CODE_HEADER_ONLY
            BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
            BOOST_DATE_TIME_NO_LIB
            BOOST_REGEX_NO_LIB
            BOOST_SYSTEM_NO_LIB
            )
endif()

if (UNIX)
    target_compile_definitions(lib_nxs INTERFACE NXS_UNIX)
endif()

#-------------------------------------------------------
#                       VERSION
#-------------------------------------------------------
set(NXS_VERSION_MAJOR 0)
set(NXS_VERSION_MINOR 1)
string(TIMESTAMP NXS_VERSION_BUILD %Y%m%d%H%M%S UTC)

configure_file(
        "${NXS_ROOT}/include/nxs/version.hpp.in"
        "${NXS_ROOT}/include/nxs/version.hpp"
)

#-------------------------------------------------------
#                     DEPENDENCIES
#-------------------------------------------------------
set(NDB_ENGINE_SQLITE ON)
add_subdirectory(${THIRD_PARTY_ROOT}/ndb ${THIRD_PARTY_ROOT}/ndb/cmake-build)

target_link_libraries(lib_nxs INTERFACE lib_ndb)