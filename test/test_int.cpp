#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestInt, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(arg_parser.get_option<int>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestInt, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    int a = arg_parser.get_option<int>("-a");
    EXPECT_EQ(4, a);


    // Test cmdarg: -b
    int b = arg_parser.get_option<int>("-b");
    EXPECT_EQ(-150, b);


    // Test cmdarg: -c
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<int>("-c"));


    // Test cmdarg: --output
    // throwing an error
    EXPECT_ANY_THROW(arg_parser.get_option<int>("--output"));
}


TEST(TestInt, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");


    // Test cmdarg: -a
    int a = arg_parser.get_option<int>("-a", 0);
    EXPECT_EQ(4, a);


    // Test cmdarg: -b
    int b = arg_parser.get_option<int>("-b", 0);
    EXPECT_EQ(-150, b);


    // Test cmdarg: -c
    // with default value 0
    int c = arg_parser.get_option<int>("-c", 0);
    EXPECT_EQ(0, c);


    // Test cmdarg: --output
    // with default value 0
    int output = arg_parser.get_option<int>("--output", 0);
    EXPECT_EQ(0, output);
}
