#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestDouble, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_double_required"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");


    // Test cmdarg: -a
    double a_value = arg_parser.get_option<double>(a);
    EXPECT_DOUBLE_EQ(4, a_value);


    // Test cmdarg: -b
    double b_value = arg_parser.get_option<double>(b);
    EXPECT_DOUBLE_EQ(-150, b_value);
}


TEST(TestDouble, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_double_optional"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");
    const auto c = arg_parser.add_arg("-c");
    const auto output = arg_parser.add_arg("--output");


    // Test cmdarg: -a
    double a_value = arg_parser.get_option<double>(a, 0);
    EXPECT_DOUBLE_EQ(4, a_value);


    // Test cmdarg: -b
    double b_value = arg_parser.get_option<double>(b, 0);
    EXPECT_DOUBLE_EQ(-150, b_value);


    // Test cmdarg: -c
    // with default value 0
    double c_value = arg_parser.get_option<double>(c, 0.0);
    EXPECT_DOUBLE_EQ(0.0, c_value);


    // Test cmdarg: --output
    // with default value 0
    double output_value = arg_parser.get_option<double>(output, 0.0);
    EXPECT_DOUBLE_EQ(0.0, output_value);
}


TEST(TestLongDouble, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_longdouble_required"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");


    // Test cmdarg: -a
    long double a_value = arg_parser.get_option<long double>(a);
    EXPECT_DOUBLE_EQ(4.0, a_value);


    // Test cmdarg: -b
    long double b_value = arg_parser.get_option<long double>(b);
    EXPECT_DOUBLE_EQ(-150.0, b_value);
}


TEST(TestLongDouble, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_longdouble_optional"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");
    const auto c = arg_parser.add_arg("-c");
    const auto output = arg_parser.add_arg("--output");


    // Test cmdarg: -a
    long double a_value = arg_parser.get_option<long double>(a, 0);
    EXPECT_DOUBLE_EQ(4.0, a_value);


    // Test cmdarg: -b
    long double b_value = arg_parser.get_option<long double>(b, 0);
    EXPECT_DOUBLE_EQ(-150.0, b_value);


    // Test cmdarg: -c
    // with default value 0
    long double c_value = arg_parser.get_option<long double>(c, 0.0);
    EXPECT_DOUBLE_EQ(0.0, c_value);


    // Test cmdarg: --output
    // with default value 0
    long double output_value = arg_parser.get_option<long double>(output, 0.0);
    EXPECT_DOUBLE_EQ(0.0, output_value);
}
