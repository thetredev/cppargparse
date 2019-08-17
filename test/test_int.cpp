#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestInt, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_int_required"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");


    // Test cmdarg: -a
    int a_value = arg_parser.get_option<int>(a);
    EXPECT_EQ(4, a_value);


    // Test cmdarg: -b
    int b_value = arg_parser.get_option<int>(b);
    EXPECT_EQ(-150, b_value);
}


TEST(TestInt, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_int_optional"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");
    const auto c = arg_parser.add_arg("-c");
    const auto output = arg_parser.add_arg("--output");


    // Test cmdarg: -a
    int a_value = arg_parser.get_option<int>(a, 0);
    EXPECT_EQ(4, a_value);


    // Test cmdarg: -b
    int b_value = arg_parser.get_option<int>(b, 0);
    EXPECT_EQ(-150, b_value);


    // Test cmdarg: -c
    // with default value 0
    int c_value = arg_parser.get_option<int>(c, 0);
    EXPECT_EQ(0, c_value);


    // Test cmdarg: --output
    // with default value 0
    int output_value = arg_parser.get_option<int>(output, 0);
    EXPECT_EQ(0, output_value);
}
