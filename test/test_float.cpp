#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestFloat, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(arg_parser.get_option<float>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestFloat, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    float a = arg_parser.get_option<float>("-a");
    EXPECT_FLOAT_EQ(4.0f, a);

    // Test cmdarg: -b
    float b = arg_parser.get_option<float>("-b");
    EXPECT_FLOAT_EQ(-150.0f, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<float>("-c"));


    // Test cmdarg: --output
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<float>("--output"));
}


TEST(TestFloat, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    float a = arg_parser.get_option<float>("-a", 0.0f);
    EXPECT_FLOAT_EQ(4.0f, a);

    // Test cmdarg: -b
    float b = arg_parser.get_option<float>("-b", 0.0f);
    EXPECT_FLOAT_EQ(-150.0f, b);


    // Test cmdarg: -c
    // with default value 0
    float c = arg_parser.get_option<float>("-c", 0.0f);
    EXPECT_FLOAT_EQ(0.0f, c);


    // Test cmdarg: --output
    // with default value 0
    float output = arg_parser.get_option<float>("--output", 0.0f);
    EXPECT_FLOAT_EQ(0.0f, output);
}
