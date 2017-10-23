cmake_minimum_required(VERSION 3.5)
project(candas CXX)

set(candas_VERSION_MAJOR 0)
set(candas_VERSION_MINOR 0)
set(candas_VERSION_PATCH 0)

list(INSERT CMAKE_MODULE_PATH 0 "${candas_SOURCE_DIR}/cmake")  # has priority -> first
include(GetGitRevision)

# ================================================================================

# enumerated candas headers
# - all paths are relative to the include-directory
# - do not include a leading '/' !!!
set(header_list
    "candas/dataframe.hpp"
    # -----
    "candas/detail/emplacer.hpp"
    "candas/detail/pack_tools.hpp"
    )

# ================================================================================

if((NOT STDLIB) AND (NOT STDLIB MATCHES ""))
    set(STDLIB libstdc++)
endif()

# ----------------------------------------

# compiler flags  --  mostly interresting for tests and examples
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++1z")
# -----
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -DDEBUG")
# -----
if($CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=${STDLIB}")
elseif($CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # no special action to link againsd libstdc++ with g++
    if(NOT ${STDLIB} MATCHES "libstdc++")
        message(WARN "g++ is only configured to use 'libstdc++' as standard library")
    endif()
endif()

# ================================================================================

get_git_revision(${candas_SOURCE_DIR})
configure_file("${PROJECT_SOURCE_DIR}/include/candas/info.hpp.in" 
               "${PROJECT_BINARY_DIR}/include/candas/info.hpp"
               )

# ================================================================================

# default to building in release mode
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

# generate lists of absolute paths
set(candas_headers )
foreach(header IN LISTS header_list)
    list(APPEND candas_headers ${candas_SOURCE_DIR}/include/${header})
endforeach(header)

# add and setup library target
add_library(candas INTERFACE)
# -----
target_sources(candas INTERFACE ${candas_headers})
target_include_directories(candas INTERFACE "${PROJECT_SOURCE_DIR}/include/"
                                            "${PROJECT_BINARY_DIR}/include/" )

# add tests
enable_testing()
add_subdirectory(tests EXCLUDE_FROM_ALL)  # test sources

