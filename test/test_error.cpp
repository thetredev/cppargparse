#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestError, CommandLineArgumentError)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t 3",
                "test_int_required"
    );


    // Add arguments
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");


    EXPECT_THROW(arg_parser.get_option<int>(a), errors::CommandLineArgumentError);
    EXPECT_THROW(arg_parser.get_option<int>(b), errors::CommandLineArgumentError);
}
