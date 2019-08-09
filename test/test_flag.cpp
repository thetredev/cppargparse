#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>


TEST(TestFlag, Flags)
{
    using namespace cppargparse;


    // Pass flags to the command line
    std::vector<const char *> passed_flags
    {
        "-t", "-x", "-e"
    };

    algorithm::collect_cmdargs(passed_flags.size(), passed_flags.data());

    // Check if all flags have been passed
    for (const auto &flag : passed_flags)
    {
        EXPECT_TRUE(parser::parse_flag(flag));
    }


    // Check flags not passed to the command line
    std::vector<const char *> invalid_flags
    {
        "-b", "-X"
    };


    for (const auto &flag : invalid_flags)
    {
        EXPECT_FALSE(parser::parse_flag(flag));
    }
}
