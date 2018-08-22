project(candas_test CXX)

# ================================================================================

# all paths relative to 'cpp' in the directory containing this file
set(test_cpp_prefix "${PROJECT_SOURCE_DIR}/cpp")
set(sources_list
    "test_info.cpp"
    "dataframe/test_construction.cpp"
    # -----
    "main.cpp"  # runner
    )

# ================================================================================

# locate Catch or fetch it
find_path(CATCH_INCLUDE_DIR  "catch2"
          PATHS ${candas_SOURCE_DIR}/lib/Catch/single_include  NO_DEFAULT_PATH )
if( (NOT CATCH_INCLUDE_DIR) OR (NOT EXISTS ${CATCH_INCLUDE_DIR}) )
    message("Could not find library: Catch -- fetching...")
    # -----
    execute_process(
        COMMAND git submodule update --init
        WORKING_DIRECTORY ${candas_SOURCE_DIR}
    )
    # -----
    set(CATCH_INCLUDE_DIR ${candas_SOURCES_DIR}/lib/Catch/single_include
        CACHE PATH "Catch include directory")
endif()

# setup Catch as a target
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR} )

# load module for detecting Catch tests
list(APPEND CMAKE_MODULE_PATH "${candas_SOURCE_DIR}/lib/Catch/contrib")
include(ParseAndAddCatchTests)

# ================================================================================

# construct sources with path
set(test_sources )
foreach(source IN LISTS sources_list)
    list(APPEND test_sources ${test_cpp_prefix}/${source})
endforeach(source)

# build test executable
set(test_exe "test-candas")
add_executable(${test_exe} ${test_sources})
# -----
target_link_libraries(${test_exe} candas)  # our library
target_link_libraries(${test_exe} Catch)   # test library
# -----
add_custom_target(check  # because CMake doesn't allow dependencies for the test target...
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS ${test_exe}
)

# add test cases
ParseAndAddCatchTests(${test_exe})

