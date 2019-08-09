
add_custom_target(tests)

add_custom_command(TARGET tests POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ctest --output-on-failure
)


function(add_unit_test test_name source_files)
    add_executable(${test_name} ${source_files})
    add_test(${test_name} ${test_name})
    add_dependencies(tests ${test_name})

    target_link_libraries(${test_name} gtest_main)
endfunction()


add_unit_test(test_flag
    ${CMAKE_CURRENT_SOURCE_DIR}/test_flag.cpp
)

add_unit_test(test_numerical
    ${CMAKE_CURRENT_SOURCE_DIR}/numerical/test_int.cpp
)
