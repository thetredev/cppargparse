#
# Testing target: tests
#

add_custom_target(tests)
add_custom_command(TARGET tests POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ctest --output-on-failure
)


#
# Testing targets: build options
#
set(TEST_BUILD_OPTIONS -Wall -pedantic)


#
# Indicator for build type "Profiling"
#
set(IS_PROFILING FALSE)
if("${CMAKE_BUILD_TYPE}" MATCHES "^(profiling|Profiling|PROFILING)$")
    set(IS_PROFILING TRUE)
endif()


#
# Profiling target: coverage
#
if(${IS_PROFILING})

    # Append "--coverage" to build options
    set(TEST_BUILD_OPTIONS ${TEST_BUILD_OPTIONS} --coverage)

    # Add target "coverage"
    add_custom_target(coverage)

    # Make "coverage" depend on "tests"
    add_dependencies(coverage tests)
endif()


#
# Function: add_unit_test()
#
# Adds a unit test executable as a target and make target <tests> depend on it.
#
function(add_unit_test test_name source_files)
    add_executable(${test_name} ${source_files})
    add_test(${test_name} ${test_name})
    add_dependencies(tests ${test_name})

    # Link unit test with gtest
    target_link_libraries(${test_name} gtest_main)

    # Add build options to test target
    target_compile_options(${test_name} PRIVATE ${TEST_BUILD_OPTIONS})

    # Link with gcov if we're on build type "Profiling"
    if(${IS_PROFILING})
        target_link_libraries(${test_name} -lgcov --coverage)
    endif()
endfunction()


#
# Unit test targets
#

# Algorithm
add_unit_test(test_algorithm
    ${CMAKE_CURRENT_SOURCE_DIR}/test_algorithm.cpp
)

# Parser
add_unit_test(test_parser
    ${CMAKE_CURRENT_SOURCE_DIR}/test_parser.cpp
)

# Arguments
add_unit_test(test_arguments
    ${CMAKE_CURRENT_SOURCE_DIR}/test_arguments.cpp
)
