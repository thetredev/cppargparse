
set(CPPARGPARSE_TEST_FLAG_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/test_flag.cpp
)

add_executable(test_flag ${CPPARGPARSE_TEST_FLAG_SRC})
target_link_libraries(test_flag gtest_main)

add_executable(cppargparse_test ${CPPARGPARSE_TEST_SRC})
