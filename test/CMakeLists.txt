#
# Testing target: tests
#
add_custom_target(tests)

add_custom_command(TARGET tests POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ctest --output-on-failure
)


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
endfunction()


#
# Unit test targets
#
add_unit_test(test_flag
    ${CMAKE_CURRENT_SOURCE_DIR}/test_flag.cpp
)

set(test_numerical_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/numerical/test_numerical.h
    ${CMAKE_CURRENT_SOURCE_DIR}/numerical/test_numerical.cpp
)

add_unit_test(test_numerical
    "${test_numerical_sources}"
)
