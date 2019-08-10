#ifndef CPPARGPARSE_TEST_NUMERICAL_H
#define CPPARGPARSE_TEST_NUMERICAL_H


#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>
#include <cppargparse/errors.h>


namespace cppargparse::test {


template <typename T>
static void numerical_required()
{
    using namespace cppargparse;

    // Pass arguments to the command line
    std::vector<const char *> cmdargs
    {
        "-a", "4",
        "-b", "-150",
        "-c", "THIS", "SHOULD", "RAISE", "AN", "ERROR",
        "--output", "/tmp/testfile"
    };

    algorithm::collect_cmdargs(cmdargs.size(), cmdargs.data());

    // Check that the options -a and -b are valid integers
    std::vector<const char *> valid_options
    {
        "-a", "-b"
    };

    for (const auto &valid_option : valid_options)
    {
        EXPECT_NO_THROW(parser::parse_arg<T>(valid_option));
    }


    // Check that the options -c and --output are invalid integers
    std::vector<const char *> invalid_options
    {
        "-c", "--output"
    };

    for (const auto &invalid_option : invalid_options)
    {
        EXPECT_ANY_THROW(parser::parse_arg<T>(invalid_option));
    }
}


template <typename T>
static void numerical_optional()
{
    using namespace cppargparse;

    // Pass arguments to the command line
    std::vector<const char *> cmdargs
    {
        "-a", "4",
        "-b", "-150",
        "-c", "THIS", "SHOULD", "RAISE", "AN", "ERROR",
        "--output", "/tmp/testfile"
    };

    algorithm::collect_cmdargs(cmdargs.size(), cmdargs.data());


    // Check that all options are valid integers
    std::vector<const char *> valid_options
    {
        "-a", "-b", "-c", "--output"
    };


    std::vector<T> parsed_values;

    for (const auto &valid_option : valid_options)
    {
        parsed_values.emplace_back(parser::parse_arg<T>(valid_option, 0));
    }

    std::vector<T> expected_values
    {
        4, -150, 0, 0
    };


    for (size_t i = 0; i < expected_values.size(); ++i)
    {
        EXPECT_TRUE(expected_values.at(i) == parsed_values.at(i));
    }
}


} // namespace cppargparse::test

#endif // CPPARGPARSE_TEST_NUMERICAL_H
