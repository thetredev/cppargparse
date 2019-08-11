#include <map>
#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>
#include <cppargparse/errors.h>

#include "test_common.h"


//
// double
//
TEST(TestDouble, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(parser::parse_arg<double>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestDouble, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    double a = parser::parse_arg<double>("-a");
    EXPECT_DOUBLE_EQ(4, a);

    // Test cmdarg: -b
    double b = parser::parse_arg<double>("-b");
    EXPECT_DOUBLE_EQ(-150, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_THROW(parser::parse_arg<double>("-c"), errors::CommandLineOptionError);


    // Test cmdarg: --output
    // throwing an error
    EXPECT_THROW(parser::parse_arg<double>("--output"), errors::CommandLineOptionError);
}


TEST(TestDouble, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    double a = parser::parse_arg<double>("-a");
    EXPECT_DOUBLE_EQ(4, a);

    // Test cmdarg: -b
    double b = parser::parse_arg<double>("-b");
    EXPECT_DOUBLE_EQ(-150, b);


    // Test cmdarg: -c
    // with default value 0
    double c = parser::parse_arg<double>("-c", 0.0);
    EXPECT_DOUBLE_EQ(0.0, c);


    // Test cmdarg: --output
    // with default value 0
    double output = parser::parse_arg<double>("--output", 0.0);
    EXPECT_DOUBLE_EQ(0.0, output);
}


//
// long double
//
TEST(TestLongDouble, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(parser::parse_arg<double>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestLongDouble, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    long double a = parser::parse_arg<long double>("-a");
    EXPECT_DOUBLE_EQ(4.0, a);

    // Test cmdarg: -b
    long double b = parser::parse_arg<long double>("-b");
    EXPECT_DOUBLE_EQ(-150.0, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_THROW(parser::parse_arg<long double>("-c"), errors::CommandLineOptionError);


    // Test cmdarg: --output
    // throwing an error
    EXPECT_THROW(parser::parse_arg<long double>("--output"), errors::CommandLineOptionError);
}


TEST(TestLongDouble, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    long double a = parser::parse_arg<long double>("-a");
    EXPECT_DOUBLE_EQ(4.0, a);

    // Test cmdarg: -b
    long double b = parser::parse_arg<long double>("-b");
    EXPECT_DOUBLE_EQ(-150.0, b);


    // Test cmdarg: -c
    // with default value 0
    long double c = parser::parse_arg<long double>("-c", 0.0);
    EXPECT_DOUBLE_EQ(0.0, c);


    // Test cmdarg: --output
    // with default value 0
    long double output = parser::parse_arg<long double>("--output", 0.0);
    EXPECT_DOUBLE_EQ(0.0, output);
}
