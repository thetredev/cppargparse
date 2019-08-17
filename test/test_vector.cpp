#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>
#include <cppargparse/errors.h>

#include "test_common.h"


template <typename T>
void test_T_values(
        cppargparse::parser::ArgumentParser &arg_parser,
        const std::vector<T> expected,
        const cppargparse::types::CommandLineArgument_t &cmdarg
    )
{
    // Test cmdarg: --people
    const std::vector<T> values = arg_parser.get_option<std::vector<T>>(cmdarg);


    EXPECT_TRUE(expected.size() == values.size());

    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected.at(i), values.at(i));
    }
}


template <typename T>
void test_T_double_values(
        cppargparse::parser::ArgumentParser &arg_parser,
        const std::vector<T> expected,
        const cppargparse::types::CommandLineArgument_t &cmdarg
    )
{
    // Test cmdarg: --people
    const std::vector<T> values = arg_parser.get_option<std::vector<T>>(cmdarg);


    EXPECT_TRUE(expected.size() == values.size());

    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(expected.at(i), values.at(i));
    }
}


TEST(TestVector, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "--people Me Myself I -i file1 file2 file3 -v 3 5 12 1 7 1200 32",
                "test_vector_required"
    );


    // Add arguments
    const auto people = arg_parser.add_arg("--people");
    const auto v = arg_parser.add_arg("-v");


    // Test cmdarg: --people
    // std::string
    test_T_values<std::string>(
                arg_parser,
                std::vector<std::string> {
                    "Me", "Myself", "I", "-i", "file1", "file2", "file3"
                },
                people
    );


    // Test cmdarg: -v
    // int
    test_T_values<int>(
                arg_parser,
                std::vector<int> {
                    3, 5, 12, 1, 7, 1200, 32
                },
                v
    );


    // Test cmdarg: -v
    // float
    test_T_values<float>(
                arg_parser,
                std::vector<float> {
                    3.0f, 5.0f, 12.0f, 1.0f, 7.0f, 1200.0f, 32.0f
                },
                v
    );


    // Test cmdarg: -v
    // double
    test_T_double_values<double>(
                arg_parser,
                std::vector<double> {
                    3, 5, 12, 1, 7, 1200, 32
                },
                v
    );


    // Test cmdarg: -v
    // long double
    test_T_double_values<long double>(
                arg_parser,
                std::vector<long double> {
                    3, 5, 12, 1, 7, 1200, 32
                },
                v
    );

    /// @todo Does GTest provide a method for testing long double values?
}



template <typename T>
void test_T_values_default(
        cppargparse::parser::ArgumentParser &arg_parser,
        const std::vector<T> expected,
        const std::vector<T> default_values,
        const cppargparse::types::CommandLineArgument_t &cmdarg
    )
{
    // Test cmdarg: --people
    const std::vector<T> values = arg_parser.get_option<std::vector<T>>(cmdarg, default_values);


    EXPECT_TRUE(expected.size() == values.size());

    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected.at(i), values.at(i));
    }
}


template <typename T>
void test_T_double_values_default(
        cppargparse::parser::ArgumentParser &arg_parser,
        const std::vector<T> expected,
        const std::vector<T> default_values,
        const cppargparse::types::CommandLineArgument_t &cmdarg
    )
{
    // Test cmdarg: --people
    const std::vector<T> values = arg_parser.get_option<std::vector<T>>(cmdarg, default_values);


    EXPECT_TRUE(expected.size() == values.size());

    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(expected.at(i), values.at(i));
    }
}


TEST(TestVector, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "--people Me Myself I -i file1 file2 file3 -v 3 5 12 1 7 1200 32",
                "test_vector_optional"
    );


    // Add arguments
    const auto people = arg_parser.add_arg("--people");
    const auto v = arg_parser.add_arg("-v");


    // Test cmdarg: --people
    // std::string
    test_T_values_default<std::string>(
                arg_parser,
                std::vector<std::string> {
                    "Me", "Myself", "I", "-i", "file1", "file2", "file3"
                },
                std::vector<std::string> {},
                people
    );


    // Test cmdarg: -v
    // int
    test_T_values_default<int>(
                arg_parser,
                std::vector<int> {
                    3, 5, 12, 1, 7, 1200, 32
                },
                std::vector<int> {},
                v
    );


    // Test cmdarg: -v
    // float
    test_T_values_default<float>(
                arg_parser,
                std::vector<float> {
                    3.0f, 5.0f, 12.0f, 1.0f, 7.0f, 1200.0f, 32.0f
                },
                std::vector<float> {},
                v
    );


    // Test cmdarg: -v
    // double
    test_T_double_values_default<double>(
                arg_parser,
                std::vector<double> {
                    3, 5, 12, 1, 7, 1200, 32
                },
                std::vector<double> {},
                v
    );


    // Test cmdarg: -v
    // long double
    test_T_double_values_default<long double>(
                arg_parser,
                std::vector<long double> {
                    3, 5, 12, 1, 7, 1200, 32
                },
                std::vector<long double> {},
                v
    );

    /// @todo Does GTest provide a method for testing long double values?
}
