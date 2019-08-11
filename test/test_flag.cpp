#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestFlag, Flags)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Add arguments
    arg_parser.add_arg("-t");
    arg_parser.add_arg("-x");


    // Test flag: -t
    const bool t = arg_parser.get_flag("-t");
    EXPECT_TRUE(t);


    // Test flag: -x
    const bool x = arg_parser.get_flag("-x");
    EXPECT_TRUE(x);


    // Test flag: -i
    // which has not been passed
    const bool i = arg_parser.get_flag("-i");
    EXPECT_FALSE(i);

    // Test flag: -p
    // which has not been passed
    const bool p = arg_parser.get_flag("-p");
    EXPECT_FALSE(p);
}
