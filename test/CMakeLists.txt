
set(CPPARGPARSE_TEST_FLAG_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/test_flag.cpp
)

add_executable(test_flag ${CPPARGPARSE_TEST_FLAG_SRC})
target_link_libraries(test_flag gtest_main)


set(CPPARGPARSE_TEST_NUMERICAL_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/numerical/test_double.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/numerical/test_float.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/numerical/test_int.cpp
)

add_executable(test_numerical ${CPPARGPARSE_TEST_NUMERICAL_SRC})
target_link_libraries(test_numerical gtest_main)
