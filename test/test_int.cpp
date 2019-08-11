#include <map>
#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>
#include <cppargparse/errors.h>

#include "test_common.h"


TEST(TestInt, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(parser::parse_arg<int>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestInt, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    int a = parser::parse_arg<int>("-a");
    EXPECT_EQ(4, a);

    // Test cmdarg: -b
    int b = parser::parse_arg<int>("-b");
    EXPECT_EQ(-150, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_THROW(parser::parse_arg<int>("-c"), errors::CommandLineOptionError);


    // Test cmdarg: --output
    // throwing an error
    EXPECT_THROW(parser::parse_arg<int>("--output"), errors::CommandLineOptionError);
}


TEST(TestInt, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    int a = parser::parse_arg<int>("-a");
    EXPECT_EQ(4, a);

    // Test cmdarg: -b
    int b = parser::parse_arg<int>("-b");
    EXPECT_EQ(-150, b);


    // Test cmdarg: -c
    // with default value 0
    int c = parser::parse_arg<int>("-c", 0);
    EXPECT_EQ(0, c);


    // Test cmdarg: --output
    // with default value 0
    int output = parser::parse_arg<int>("--output", 0);
    EXPECT_EQ(0, output);
}
