#include <algorithm>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


//
// find_arg(<invalid arg ID>)
//
TEST(TestAlgorithm, FindArgByInvalidID)
{
    using namespace cppargparse;

    const types::CommandLineArguments_t cmdargs;

    const auto position = algorithm::find_arg(cmdargs, "-t");
    ASSERT_EQ(cmdargs.cend(), position);
}


//
// find_arg(<valid arg ID>)
//
TEST(TestAlgorithm, FindArgByValidID)
{
    using namespace cppargparse;

    const types::CommandLine_t cmd {
        "-t", "3"
    };

    const types::CommandLineArguments_t cmdargs {
        {
            "-t", std::string(), std::string(), cmd.cbegin()
        }
    };


    const auto position = algorithm::find_arg(cmdargs, "-t");
    ASSERT_EQ(cmdargs.cbegin(), position);
}


//
// find_arg(<valid arg AlternativeID>)
//
TEST(TestAlgorithm, FindArgByValidAlternativeID)
{
    using namespace cppargparse;

    const types::CommandLine_t cmd {
        "--time", "3"
    };


    const types::CommandLineArguments_t cmdargs {
        {
            "-t", "--time", std::string(), cmd.cbegin()
        }
    };


    const auto position = algorithm::find_arg(cmdargs, "--time");
    ASSERT_EQ(cmdargs.cbegin(), position);
}


//
// find_arg(<invalid arg ID | invalid arg AlternativeID>)
//
TEST(TestAlgorithm, FindArgByInvalidIDs)
{
    using namespace cppargparse;

    const types::CommandLine_t cmd {
        "--time", "3"
    };


    const types::CommandLineArguments_t cmdargs {
        {
            "-f", "--frozen", std::string(), cmd.cend()
        }
    };


    const auto position = algorithm::find_arg(cmdargs, "--time");
    ASSERT_EQ(cmdargs.cend(), position);
}


//
// find_arg_position(<empty CMD>)
//
TEST(TestAlgorithm, FindArgPositionWithEmptyCMD)
{
    using namespace cppargparse;

    const types::CommandLine_t cmd;


    const auto cmd_position = algorithm::find_arg_position(cmd, "-t", "--time");
    ASSERT_EQ(cmd.cend(), cmd_position);
}


//
// find_arg_position(<valid arg ID>)
//
TEST(TestAlgorithm, FindArgPositionByValidID)
{
    using namespace cppargparse;

    const types::CommandLine_t cmd {
        "-t", "3"
    };


    const auto cmd_position = algorithm::find_arg_position(cmd, "-t", "--time");
    ASSERT_EQ(cmd.cbegin(), cmd_position);
}


//
// find_arg_position(<invalid arg ID>)
//
TEST(TestAlgorithm, FindArgPositionByInvalidID)
{
    using namespace cppargparse;

    const types::CommandLine_t cmd {
        "-t", "3", "-f", "5"
    };



    const auto cmd_position = algorithm::find_arg_position(cmd, "-y", "--yes");


    auto expected_position = cmd.cbegin();
    std::advance(expected_position, 2);

    ASSERT_EQ(cmd.cend(), cmd_position);
}
