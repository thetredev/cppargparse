#include <map>
#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>
#include <cppargparse/errors.h>

#include "test_common.h"


TEST(TestFloat, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(parser::parse_arg<float>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestFloat, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    float a = parser::parse_arg<float>("-a");
    EXPECT_FLOAT_EQ(4.0f, a);

    // Test cmdarg: -b
    float b = parser::parse_arg<float>("-b");
    EXPECT_FLOAT_EQ(-150.0f, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_THROW(parser::parse_arg<float>("-c"), errors::CommandLineOptionError);


    // Test cmdarg: --output
    // throwing an error
    EXPECT_THROW(parser::parse_arg<float>("--output"), errors::CommandLineOptionError);
}


TEST(TestFloat, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs();


    // Test cmdarg: -a
    float a = parser::parse_arg<float>("-a");
    EXPECT_FLOAT_EQ(4.0f, a);

    // Test cmdarg: -b
    float b = parser::parse_arg<float>("-b");
    EXPECT_FLOAT_EQ(-150.0f, b);


    // Test cmdarg: -c
    // with default value 0
    float c = parser::parse_arg<float>("-c", 0.0f);
    EXPECT_FLOAT_EQ(0.0f, c);


    // Test cmdarg: --output
    // with default value 0
    float output = parser::parse_arg<float>("--output", 0.0f);
    EXPECT_FLOAT_EQ(0.0f, output);
}
