#include <functional>
#include <limits>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"



// -------------------------
// - ASSERT_*_EQ wrappers
// -------------------------

template <typename T>
void assert_eq_wrap(const T &v1, const T &v2)
{
    ASSERT_EQ(v1, v2);
}


template <>
void assert_eq_wrap<double>(const double &v1, const double &v2)
{
    ASSERT_DOUBLE_EQ(v1, v2);
}


template <>
void assert_eq_wrap<long double>(const long double &v1, const long double &v2)
{
    assert_eq_wrap<double>(static_cast<double>(v1), static_cast<double>(v2));
}


template <>
void assert_eq_wrap<float>(const float &v1, const float &v2)
{
    ASSERT_FLOAT_EQ(v1, v2);
}


// -------------------------
// - Helper functions
// -------------------------

template <typename T>
void value_test(const T &value, const T &default_value)
{
    using namespace cppargparse;

    // Generate a command line argument string with "-t <value>"
    std::ostringstream cmd;
    cmd << "-t " << std::fixed << std::setprecision(15) << value;


    // Expect the same number as <value> when parsing the command line string for "-t"
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs(cmd.str()), "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    assert_eq_wrap<T>(value, arg_parser.get_option<T>(t));


    // Check default value behavior
    const auto x = arg_parser.add_arg("-x");
    assert_eq_wrap<T>(default_value, arg_parser.get_option<T>(x, default_value));
}


template <typename T>
void max_test(const bool out_of_range)
{
    using namespace cppargparse;

    const T max = std::numeric_limits<T>::max();

    // Generate a command line argument string with <max>
    std::ostringstream cmd;
    cmd << "-t " << std::fixed << std::setprecision(30) << max;

    // If we're testing for out of range, add a 0 to <cmd>
    if (out_of_range)
    {
        cmd << '0';
    }

    // Expect the same number as <max> when parsing the command line string for "-t"
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs(cmd.str()), "TestArguments");

    const auto t = arg_parser.add_arg("-t");

    // If we're testing for out of range, expect an error...
    if (out_of_range)
    {
        ASSERT_THROW(arg_parser.get_option<T>(t), errors::CommandLineOptionError);
    }
    else
    {
        // ... else, check for value equality of <max> and the parsed value in <cmd>
        assert_eq_wrap<T>(max, arg_parser.get_option<T>(t));
    }
}


template <typename T>
void vector_test(const std::vector<T> &seq_expected, const bool reach_end, const bool reach_end_should_throw = true)
{
    using namespace cppargparse;


    // Generate a command line argument string with the expected sequence
    std::ostringstream cmd;
    cmd << "--seq";

    for (const auto &seq_value : seq_expected)
    {
        cmd << ' ' << std::fixed << std::setprecision(15) << seq_value;
    }


    // If we should reach the end, add another argument to the end
    if (reach_end)
    {
        cmd << " -t 3";
    }


    // Parse the command line string
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs(cmd.str()), "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");


    // If we should reach the end, parsing the command line like that...
    if (reach_end)
    {
        if (reach_end_should_throw)
        {
            // ... should throw an error
            ASSERT_THROW(arg_parser.get_option<std::vector<T>>(seq), errors::CommandLineOptionError);
        }

        // ... so, add the next argument to the parser
        arg_parser.add_arg("-t");
    }


    // Check for the equality of expected and parsed values
    const std::vector<T> seq_parsed = arg_parser.get_option<std::vector<T>>(seq);

    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        assert_eq_wrap<T>(seq_expected.at(i), seq_parsed.at(i));
    }
}



// -------------------------
// - Unit tests
// -------------------------


//
// char
//
TEST(TestArguments, Char)
{
    value_test<char>('a', 'b');
}

TEST(TestArguments, CharsVector)
{
    vector_test<char>({'3', '2', '3', '6', '2', 'C'}, false);
}

TEST(TestArguments, CharsVectorReachEnd)
{
    vector_test<char>({'3', '2', '3', '6', '2', 'C'}, true, false);
}


//
// unsigned char
//
TEST(TestArguments, UnsignedChar)
{
    value_test<unsigned char>('a', 'b');
}

TEST(TestArguments, UnsignedCharsVector)
{
    vector_test<unsigned char>({'3', '2', '3', '6', '2', 'C'}, false);
}

TEST(TestArguments, UnsignedCharsVectorReachEnd)
{
    vector_test<unsigned char>({'3', '2', '3', '6', '2', 'C'}, true, false);
}


//
// int
//
TEST(TestArguments, Int)
{
    value_test<int>(3, 5);
}


TEST(TestArguments, IntMax)
{
    max_test<int>(false);
}

TEST(TestArguments, IntOutOfRange)
{
    max_test<int>(true);
}


TEST(TestArguments, IntsVector)
{
    vector_test<int>({3, 2, 34, 6, 2, 100, 2151112}, false);
}

TEST(TestArguments, IntsVectorReachEnd)
{
    vector_test<int>({3, 2, 34, 6, 2, 100, 2151112}, true);
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
    max_test<unsigned int>(false);
}

TEST(TestArguments, UnsignedIntOutOfRange)
{
    max_test<unsigned int>(true);
}

TEST(TestArguments, UnsignedIntsVector)
{
    vector_test<unsigned int>({3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, false);
}

TEST(TestArguments, UnsignedIntsVectorReachEnd)
{
    vector_test<unsigned int>({3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, true);
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
    max_test<long>(false);
}

TEST(TestArguments, LongOutOfRange)
{
    max_test<long>(true);
}

TEST(TestArguments, LongsVector)
{
    vector_test<long>({3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, false);
}

TEST(TestArguments, LongsVectorReachEnd)
{
    vector_test<long>({3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, true);
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
    max_test<unsigned long>(false);
}

TEST(TestArguments, UnsignedLongOutOfRange)
{
    max_test<unsigned long>(true);
}

TEST(TestArguments, UnsignedLongsVector)
{
    vector_test<unsigned long>({3ul, 2ul, 34ul, 6ul, 2ul, 100ul, 2151112ul}, false);
}

TEST(TestArguments, UnsignedLongsVectorReachEnd)
{
    vector_test<unsigned long>({3ul, 2ul, 34ul, 6ul, 2l, 100ul, 2151112ul}, true);
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
    max_test<long long>(false);
}

TEST(TestArguments, LongLongOutOfRange)
{
    max_test<long long>(true);
}

TEST(TestArguments, LongLongsVector)
{
    vector_test<long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, false);
}

TEST(TestArguments, LongLongsVectorReachEnd)
{
    vector_test<long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, true);
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
    max_test<unsigned long long>(false);
}

TEST(TestArguments, UnsignedLongLongOutOfRange)
{
    max_test<unsigned long long>(true);
}

TEST(TestArguments, UnsignedLongLongsVector)
{
    vector_test<unsigned long long>({3ull, 2ull, 34ull, 6ull, 2ull, 100ull, 2151112ull}, false);
}

TEST(TestArguments, UnsignedLongLongsVectorReachEnd)
{
    vector_test<unsigned long long>({3ull, 2ull, 34ull, 6ull, 2ull, 100ull, 2151112ull}, true);
}


//
// float
//
TEST(TestArguments, Float)
{
    value_test<float>(3.0f, 5.0f);
}

TEST(TestArguments, FloatMax)
{
    max_test<float>(false);
}

/*
TEST(TestArguments, FloatOutOfRange)
{
    max_test<float>(true);
}
*/

TEST(TestArguments, FloatsVector)
{
    vector_test<float>({3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151.1112f}, false);
}

TEST(TestArguments, FloatsVectorReachEnd)
{
    vector_test<float>({3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151.1112f}, true);
}


//
// double
//
TEST(TestArguments, Double)
{
    value_test<double>(3.63126121, 5.0);
}

TEST(TestArguments, DoubleMax)
{
    max_test<double>(false);
}

/*
TEST(TestArguments, DoubleOutOfRange)
{
    max_test<double>(true);
}
*/

TEST(TestArguments, DoublesVector)
{
    vector_test<double>({3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151.1112}, false);
}

TEST(TestArguments, DoublesVectorReachEnd)
{
    vector_test<double>({3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151.1112}, true);
}


//
// long double
//
TEST(TestArguments, LongDouble)
{
    value_test<long double>(3.63126121l, 5.0l);
}

TEST(TestArguments, LongDoubleMax)
{
    max_test<long double>(false);
}

/*
TEST(TestArguments, LongDoubleOutOfRange)
{
    max_test<long double>(true);
}
*/

TEST(TestArguments, LongDoublesVector)
{
    vector_test<long double>({3.2l, 2.0l, 34.0l, 6.0l, 2.0l, 100.0l, 2151.1112l}, false);
}

TEST(TestArguments, LongDoublesVectorReachEnd)
{
    vector_test<long double>({3.2l, 2.0l, 34.0l, 6.0l, 2.0l, 100.0l, 2151.1112l}, true);
}


//
// std::string
//
TEST(TestArguments, String)
{
    value_test<std::string>("/usr/include/cppargparse", "DEFAULT");
}

TEST(TestArguments, StringReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("--text THIS IS SAMPLE TEXT -c"), "TestArguments");

    const auto c = arg_parser.add_arg("-c");
    ASSERT_THROW(arg_parser.get_option<std::string>(c), errors::CommandLineOptionError);
}

TEST(TestArguments, StringsVector)
{
    vector_test<std::string>({"THIS", "IS", "SAMPLE", "TEXT"}, false);
}

TEST(TestArguments, StringsVectorReachEnd)
{
    vector_test<std::string>({"THIS", "IS", "SAMPLE", "TEXT"}, true, false);
}
