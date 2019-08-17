#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestFloat, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_float_required"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");


    // Test cmdarg: -a
    float a_value = arg_parser.get_option<float>(a);
    EXPECT_FLOAT_EQ(4.0f, a_value);

    // Test cmdarg: -b
    float b_value = arg_parser.get_option<float>(b);
    EXPECT_FLOAT_EQ(-150.0f, b_value);
}


TEST(TestFloat, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_float_optional"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");
    const auto c = arg_parser.add_arg("-c");
    const auto output = arg_parser.add_arg("--output");


    // Test cmdarg: -a
    float a_value = arg_parser.get_option<float>(a, 0.0f);
    EXPECT_FLOAT_EQ(4.0f, a_value);

    // Test cmdarg: -b
    float b_value = arg_parser.get_option<float>(b, 0.0f);
    EXPECT_FLOAT_EQ(-150.0f, b_value);


    // Test cmdarg: -c
    // with default value 0
    float c_value = arg_parser.get_option<float>(c, 0.0f);
    EXPECT_FLOAT_EQ(0.0f, c_value);


    // Test cmdarg: --output
    // with default value 0
    float output_value = arg_parser.get_option<float>(output, 0.0f);
    EXPECT_FLOAT_EQ(0.0f, output_value);
}
