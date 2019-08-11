#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestFlag, Flags)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test flag: -t
    const bool t = parser::parse_flag("-t");
    EXPECT_TRUE(t);

    // Test flag: -x
    const bool x = parser::parse_flag("-x");
    EXPECT_TRUE(x);


    // Test flag: -i
    // which has not been passed
    const bool i = parser::parse_flag("-i");
    EXPECT_FALSE(i);

    // Test flag: -p
    // which has not been passed
    const bool p = parser::parse_flag("-p");
    EXPECT_FALSE(p);
}
