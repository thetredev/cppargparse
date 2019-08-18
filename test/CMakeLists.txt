#
# Testing target: tests
#

add_custom_target(run_tests)
add_custom_command(TARGET run_tests POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ctest --output-on-failure
)


add_custom_target(tests)
add_dependencies(run_tests tests)


set(TEST_BUILD_OPTIONS -Wall -Wno-long-long -pedantic)

string(TOLOWER ${CMAKE_GENERATOR} BUILD_GENERATOR)


#
# Profiling target: coverage
#
if("${CMAKE_BUILD_TYPE}" MATCHES "^(profiling|Profiling|PROFILING)$")

    set(TEST_BUILD_OPTIONS ${TEST_BUILD_OPTIONS} --coverage)

    add_custom_target(coverage)

    add_custom_command(TARGET coverage POST_BUILD
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

        COMMAND lcov --capture --config-file ${CMAKE_SOURCE_DIR}/lcovrc --directory . --include ${CMAKE_SOURCE_DIR}/include/*.h --output cppargparse.info
        COMMAND genhtml --branch-coverage --output coverage cppargparse.info
    )

    add_dependencies(coverage run_tests)
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

    target_compile_options(${test_name} PRIVATE ${TEST_BUILD_OPTIONS})

    if("${CMAKE_BUILD_TYPE}" MATCHES "^(profiling|Profiling|PROFILING)$")
        target_link_options(${test_name} PRIVATE -lgcov --coverage)
    endif()
endfunction()


#
# Unit test targets
#

# Flag
add_unit_test(test_flag
    ${CMAKE_CURRENT_SOURCE_DIR}/test_flag.cpp
)


# Numerical
add_unit_test(test_double
    ${CMAKE_CURRENT_SOURCE_DIR}/test_double.cpp
)

add_unit_test(test_int
    ${CMAKE_CURRENT_SOURCE_DIR}/test_int.cpp
)

add_unit_test(test_float
    ${CMAKE_CURRENT_SOURCE_DIR}/test_float.cpp
)


# String
add_unit_test(test_string
    ${CMAKE_CURRENT_SOURCE_DIR}/test_string.cpp
)


# Vector
add_unit_test(test_vector
    ${CMAKE_CURRENT_SOURCE_DIR}/test_vector.cpp
)


# Error
add_unit_test(test_error
    ${CMAKE_CURRENT_SOURCE_DIR}/test_error.cpp
)
