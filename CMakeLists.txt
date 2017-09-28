cmake_minimum_required(VERSION 3.5)
project(candas
        VERSION "0.0.0"
        LANGUAGES CXX )

set(CMAKE_MODULE_PATH "${candas_SOURCE_DIR}/cmake")
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

# compiler flags  --  mostly interresting for tests and examples
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++1z")  # common for all below
# -----
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -DDEBUG")

# ================================================================================

set(GIT_DIR "${candas_SOURCE_DIR}/.git")
if((EXISTS ${GIT_DIR}) AND (EXISTS "${GIT_DIR}/HEAD"))
    # create a data directory if needed
    set(GIT_DATA_DIR "${candas_BINARY_DIR}/CMakeFiles/git-data")
    if(NOT EXISTS ${GIT_DATA_DIR})
        file(MAKE_DIRECTORY ${GIT_DATA_DIR})
    endif()
    # determine ref
    set(HEAD_FILE "${GIT_DATA_DIR}/head")
    configure_file("${GIT_DIR}/HEAD" ${HEAD_FILE} COPYONLY)
    file(READ ${HEAD_FILE} HEAD_CONTENTS LIMIT 1024)
    string(STRIP "${HEAD_CONTENTS}" HEAD_CONTENTS)
    if(HEAD_CONTENTS MATCHES "ref:")

    else()
        # at a detached head
        configure_file("${GIT_DIR}/HEAD" "${GIT_DATA_DIR}/head-ref" COPYONLY) 
    endif()

endif()

# ================================================================================

get_git_revision(${candas_SOURCE_DIR})
string(TOLOWER "${GIT_REPO_CLEAN}" GIT_REPO_CLEAN_BOOL_STR)
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

