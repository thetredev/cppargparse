#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


//
// double
//
TEST(TestDouble, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(arg_parser.get_option<double>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestDouble, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    double a = arg_parser.get_option<double>("-a");
    EXPECT_DOUBLE_EQ(4, a);


    // Test cmdarg: -b
    double b = arg_parser.get_option<double>("-b");
    EXPECT_DOUBLE_EQ(-150, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<double>("-c"));

    // Test cmdarg: --output
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<double>("--output"));
}


TEST(TestDouble, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    double a = arg_parser.get_option<double>("-a", 0);
    EXPECT_DOUBLE_EQ(4, a);


    // Test cmdarg: -b
    double b = arg_parser.get_option<double>("-b", 0);
    EXPECT_DOUBLE_EQ(-150, b);


    // Test cmdarg: -c
    // with default value 0
    double c = arg_parser.get_option<double>("-c", 0.0);
    EXPECT_DOUBLE_EQ(0.0, c);


    // Test cmdarg: --output
    // with default value 0
    double output = arg_parser.get_option<double>("--output", 0.0);
    EXPECT_DOUBLE_EQ(0.0, output);
}


//
// long double
//
TEST(TestLongDouble, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(arg_parser.get_option<double>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestLongDouble, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    long double a = arg_parser.get_option<long double>("-a");
    EXPECT_DOUBLE_EQ(4.0, a);


    // Test cmdarg: -b
    long double b = arg_parser.get_option<long double>("-b");
    EXPECT_DOUBLE_EQ(-150.0, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<long double>("-c"));


    // Test cmdarg: --output
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<long double>("--output"));
}


TEST(TestLongDouble, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    long double a = arg_parser.get_option<long double>("-a", 0);
    EXPECT_DOUBLE_EQ(4.0, a);


    // Test cmdarg: -b
    long double b = arg_parser.get_option<long double>("-b", 0);
    EXPECT_DOUBLE_EQ(-150.0, b);


    // Test cmdarg: -c
    // with default value 0
    long double c = arg_parser.get_option<long double>("-c", 0.0);
    EXPECT_DOUBLE_EQ(0.0, c);


    // Test cmdarg: --output
    // with default value 0
    long double output = arg_parser.get_option<long double>("--output", 0.0);
    EXPECT_DOUBLE_EQ(0.0, output);
}
