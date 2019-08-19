#include <limits>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"



// -------------------------
// - Helper functions
// -------------------------

template <typename T>
void value_test(const T &value, const T &default_value)
{
    using namespace cppargparse;

    // Generate a command line argument string with "-t <value>"
    std::ostringstream cmd;
    cmd << "-t " << value;


    // Expect the same number as <value> when parsing the command line string for "-t"
    auto arg_parser = test::parse_cmdargs(cmd.str(), "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(value, arg_parser.get_option<T>(t));


    // Check default value behavior
    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(default_value, arg_parser.get_option<T>(x, default_value));
}


template <typename T>
void max_test(const T &max)
{
    using namespace cppargparse;

    // Generate a command line argument string with <max>
    std::ostringstream cmd;
    cmd << "-t " << max;

    // Expect the same number as <max> when parsing the command line string for "-t"
    auto arg_parser = test::parse_cmdargs(cmd.str(), "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(max, arg_parser.get_option<T>(t));
}


template <typename T>
void out_of_range_test(const T &max)
{
    using namespace cppargparse;

    // Generate a command line argument string with a number that's higher than <max>
    std::ostringstream cmd;
    cmd << "-t " << max << '0';


    // Expect an error when parsing the command line string for "-t" with the out-of-range number
    auto arg_parser = test::parse_cmdargs(cmd.str(), "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_THROW(arg_parser.get_option<T>(t), errors::CommandLineOptionError);
}


template <typename T>
void vector_test(const std::vector<T> &seq_expected, bool reach_end)
{
    using namespace cppargparse;


    // Generate a command line argument string with the expected sequence
    std::ostringstream cmd;
    cmd << "--seq";

    for (const auto &seq_value : seq_expected)
    {
        cmd << ' ' << seq_value;
    }


    // If we should reach the end, add another argument to the end
    if (reach_end)
    {
        cmd << " -t 3";
    }


    // Parse the command line string
    auto arg_parser = test::parse_cmdargs(cmd.str(), "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");


    // If we should reach the end, parsing the command line like that should throw an error...
    if (reach_end)
    {
        ASSERT_THROW(arg_parser.get_option<std::vector<T>>(seq), errors::CommandLineOptionError);

        // ... so, add the next argument to the parser
        arg_parser.add_arg("-t");
    }


    // Check for the equality of expected and parsed values
    const std::vector<T> seq_parsed = arg_parser.get_option<std::vector<T>>(seq);

    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_parsed.at(i));
    }
}



// -------------------------
// - Unit tests
// -------------------------


//
// int
//
TEST(TestArguments, Int)
{
    value_test<int>(3, 5);
}

TEST(TestArguments, IntMax)
{
    max_test(std::numeric_limits<int>::max());
}

TEST(TestArguments, IntOutOfRange)
{
    out_of_range_test(std::numeric_limits<int>::max());
}

TEST(TestArguments, IntsVector)
{
    vector_test<int>(std::vector<int> {3, 2, 34, 6, 2, 100, 2151112}, false);
}

TEST(TestArguments, IntsVectorReachEnd)
{
    vector_test<int>(std::vector<int> {3, 2, 34, 6, 2, 100, 2151112}, true);
}


//
// unsigned int
//
TEST(TestArguments, UnsignedInt)
{
    value_test<unsigned int>(3u, 5u);
}

TEST(TestArguments, UnsignedIntMax)
{
    max_test(std::numeric_limits<unsigned int>::max());
}

TEST(TestArguments, UnsignedIntOutOfRange)
{
    out_of_range_test(std::numeric_limits<unsigned int>::max());
}

TEST(TestArguments, UnsignedIntsVector)
{
    vector_test<unsigned int>(std::vector<unsigned int> {3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, false);
}

TEST(TestArguments, UnsignedIntsVectorReachEnd)
{
    vector_test<unsigned int>(std::vector<unsigned int> {3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, true);
}


//
// long
//
TEST(TestArguments, Long)
{
    value_test<long>(3l, 5l);
}

TEST(TestArguments, LongMax)
{
    max_test(std::numeric_limits<long>::max());
}

TEST(TestArguments, LongOutOfRange)
{
    out_of_range_test(std::numeric_limits<long>::max());
}

TEST(TestArguments, LongsVector)
{
    vector_test<long>(std::vector<long> {3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, false);
}

TEST(TestArguments, LongsVectorReachEnd)
{
    vector_test<long>(std::vector<long> {3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, true);
}


//
// unsigned long
//
TEST(TestArguments, UnsignedLong)
{
    value_test<unsigned long>(3ul, 5ul);
}

TEST(TestArguments, UnsignedLongMax)
{
    max_test(std::numeric_limits<unsigned long>::max());
}

TEST(TestArguments, UnsignedLongOutOfRange)
{
    out_of_range_test(std::numeric_limits<unsigned long>::max());
}

TEST(TestArguments, UnsignedLongsVector)
{
    vector_test<unsigned long>(
                std::vector<unsigned long> {3ul, 2ul, 34ul, 6ul, 2ul, 100ul, 2151112ul}, false);
}

TEST(TestArguments, UnsignedLongsVectorReachEnd)
{
    vector_test<unsigned long>(
                std::vector<unsigned long> {3ul, 2ul, 34ul, 6ul, 2l, 100ul, 2151112ul}, true);
}


//
// long long
//
TEST(TestArguments, LongLong)
{
    value_test<long long>(3l, 5l);
}

TEST(TestArguments, LongLongMax)
{
    max_test(std::numeric_limits<long long>::max());
}

TEST(TestArguments, LongLongOutOfRange)
{
    out_of_range_test(std::numeric_limits<long long>::max());
}

TEST(TestArguments, LongLongsVector)
{
    vector_test<long long>(
                std::vector<long long> {3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, false);
}

TEST(TestArguments, LongLongsVectorReachEnd)
{
    vector_test<long long>(
                std::vector<long long> {3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, true);
}


//
// unsigned long long
//
TEST(TestArguments, UnsignedLongLong)
{
    value_test<unsigned long long>(3l, 5l);
}

TEST(TestArguments, UnsignedLongLongMax)
{
    max_test(std::numeric_limits<unsigned long long>::max());
}

TEST(TestArguments, UnsignedLongLongOutOfRange)
{
    out_of_range_test(std::numeric_limits<unsigned long long>::max());
}

TEST(TestArguments, UnsignedLongLongsVector)
{
    vector_test<unsigned long long>(
                std::vector<unsigned long long> {3ull, 2ull, 34ull, 6ull, 2ull, 100ull, 2151112ull}, false);
}

TEST(TestArguments, UnsignedLongLongsVectorReachEnd)
{
    vector_test<unsigned long long>(
                std::vector<unsigned long long> {3ull, 2ull, 34ull, 6ull, 2ull, 100ull, 2151112ull}, true);
}


//
// float
//
TEST(TestArguments, Float)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_FLOAT_EQ(3.0f, arg_parser.get_option<float>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_FLOAT_EQ(5.0f, arg_parser.get_option<float>(x, 5));
}

//
// vector of floats
//
TEST(TestArguments, VectorOfFloats)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3.2 2 34 6 2 100 2151112", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<float> seq_values = arg_parser.get_option<std::vector<float>>(seq);

    const std::vector<float> seq_expected {
        3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151112.0f
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_FLOAT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of floats reach end
//
TEST(TestArguments, VectorOfFloatsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3.2 2 34 6 2 100 2151112 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<float> seq_values = arg_parser.get_option<std::vector<float>>(seq);

    const std::vector<float> seq_expected {
        3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151112.0f
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_FLOAT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// double
//
TEST(TestArguments, Double)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3.63126121", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_DOUBLE_EQ(3.63126121, arg_parser.get_option<double>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_DOUBLE_EQ(5.0, arg_parser.get_option<double>(x, 5));
}

//
// vector of doubles
//
TEST(TestArguments, VectorOfDoubles)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3.2 2 34 6 2 100 2151112.11111", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<double> seq_values = arg_parser.get_option<std::vector<double>>(seq);

    const std::vector<double> seq_expected {
        3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151112.11111
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of doubles reach end
//
TEST(TestArguments, VectorOfDoublesReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3.2 2 34 6 2 100 2151112.11111 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<double> seq_values = arg_parser.get_option<std::vector<double>>(seq);

    const std::vector<double> seq_expected {
        3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151112.11111
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// long double
//
TEST(TestArguments, LongDouble)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3.63126121", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_DOUBLE_EQ(3.63126121, arg_parser.get_option<long double>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_DOUBLE_EQ(5.0, arg_parser.get_option<long double>(x, 5));
}

//
// vector of long doubles
//
TEST(TestArguments, VectorOfLongDoubles)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3.2 2 34 6 2 100 2151112.11111", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<long double> seq_values = arg_parser.get_option<std::vector<long double>>(seq);

    const std::vector<long double> seq_expected {
        3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151112.11111
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of long doubles reach end
//
TEST(TestArguments, VectorOfLongDoublesReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3.2 2 34 6 2 100 2151112.11111 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<long double> seq_values = arg_parser.get_option<std::vector<long double>>(seq);

    const std::vector<long double> seq_expected {
        3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151112.11111
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_DOUBLE_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// string
//
TEST(TestArguments, String)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--text THIS IS SAMPLE TEXT", "TestArguments");

    const auto t = arg_parser.add_arg("-t", "--text");
    ASSERT_EQ("THIS", arg_parser.get_option<std::string>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ("DEFAULT", arg_parser.get_option<std::string>(x, "DEFAULT"));
}

//
// string reach end
//
TEST(TestArguments, StringReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--text THIS IS SAMPLE TEXT -c", "TestArguments");

    const auto t = arg_parser.add_arg("-t", "--text");
    ASSERT_EQ("THIS", arg_parser.get_option<std::string>(t));

    const auto c = arg_parser.add_arg("-c");
    ASSERT_THROW(arg_parser.get_option<std::string>(c), errors::CommandLineOptionError);
}


//
// vector of strings
//
TEST(TestArguments, VectorOfStrings)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--text THIS IS SAMPLE TEXT", "TestArguments");

    const auto t = arg_parser.add_arg("-t", "--text");
    const std::vector<std::string> text_values = arg_parser.get_option<std::vector<std::string>>(t);

    const std::vector<std::string> text_expected {
        "THIS", "IS", "SAMPLE", "TEXT"
    };

    for (size_t i = 0; i < text_expected.size(); ++i)
    {
        ASSERT_EQ(text_expected.at(i), text_values.at(i));
    }
}

//
// vector of strings reach end
//
TEST(TestArguments, VectorOfStringsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--text THIS IS SAMPLE TEXT -x 0", "TestArguments");

    const auto t = arg_parser.add_arg("-t", "--text");
    arg_parser.add_arg("-x");

    const std::vector<std::string> text_values = arg_parser.get_option<std::vector<std::string>>(t);

    const std::vector<std::string> text_expected {
        "THIS", "IS", "SAMPLE", "TEXT"
    };

    for (size_t i = 0; i < text_expected.size(); ++i)
    {
        ASSERT_EQ(text_expected.at(i), text_values.at(i));
    }
}
