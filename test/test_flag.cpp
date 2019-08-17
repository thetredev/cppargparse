#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestFlag, Flags)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_flag"
    );


    // Add arguments
    const auto t = arg_parser.add_arg("-t");
    const auto x = arg_parser.add_arg("-x");


    // Test flag: -t
    const bool t_passed = arg_parser.get_flag(t);
    EXPECT_TRUE(t_passed);


    // Test flag: -x
    const bool x_passed = arg_parser.get_flag(x);
    EXPECT_TRUE(x_passed);
}
