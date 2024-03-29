#include <functional>
#include <limits>
#include <list>
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


template <typename T>
void list_test(const std::vector<T> &seq_expected, const bool reach_end, const bool reach_end_should_throw = true)
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
            ASSERT_THROW(arg_parser.get_option<std::list<T>>(seq), errors::CommandLineOptionError);
        }

        // ... so, add the next argument to the parser
        arg_parser.add_arg("-t");
    }


    // Check for the equality of expected and parsed values
    const std::list<T> seq_parsed = arg_parser.get_option<std::list<T>>(seq);

    auto it_expected = seq_expected.cbegin();
    auto it_parsed = seq_parsed.cbegin();

    while (it_expected != seq_expected.cend())
    {
        assert_eq_wrap<T>(*it_expected, *it_parsed);

        ++it_expected;
        ++it_parsed;
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

TEST(TestArguments, CharVector)
{
    vector_test<char>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, CharVectorReachEnd)
{
    vector_test<char>({3, 2, 3, 6, 2, 'C'}, true, false);
}

TEST(TestArguments, CharList)
{
    list_test<char>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, CharListReachEnd)
{
    list_test<char>({3, 2, 3, 6, 2, 'C'}, true, false);
}


//
// unsigned char
//
TEST(TestArguments, UnsignedChar)
{
    value_test<unsigned char>('a', 'b');
}

TEST(TestArguments, UnsignedCharMax)
{
    max_test<unsigned char>(false);
}

TEST(TestArguments, UnsignedCharVector)
{
    vector_test<unsigned char>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, UnsignedCharVectorReachEnd)
{
    vector_test<unsigned char>({3, 2, 3, 6, 2, 'C'}, true, false);
}

TEST(TestArguments, UnsignedCharList)
{
    list_test<unsigned char>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, UnsignedCharListReachEnd)
{
    list_test<unsigned char>({3, 2, 3, 6, 2, 'C'}, true, false);
}


//
// int8_t
//
TEST(TestArguments, Int8)
{
    value_test<int8_t>(5, 'a');
}

TEST(TestArguments, Int8Max)
{
    max_test<int8_t>(false);
}

TEST(TestArguments, Int8Vector)
{
    vector_test<int8_t>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, Int8VectorReachEnd)
{
    vector_test<int8_t>({3, 2, 3, 6, 2, 'C'}, true, false);
}

TEST(TestArguments, Int8List)
{
    list_test<int8_t>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, Int8ListReachEnd)
{
    list_test<int8_t>({3, 2, 3, 6, 2, 'C'}, true, false);
}


//
// uint8_t
//
TEST(TestArguments, UInt8)
{
    value_test<uint8_t>(8u, 'a');
}

TEST(TestArguments, UInt8Max)
{
    max_test<uint8_t>(false);
}

TEST(TestArguments, UInt8Vector)
{
    vector_test<uint8_t>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, UInt8VectorReachEnd)
{
    vector_test<uint8_t>({3, 2, 3, 6, 2, 'C'}, true, false);
}

TEST(TestArguments, UInt8List)
{
    list_test<uint8_t>({3, 2, 3, 6, 2, 'C'}, false);
}

TEST(TestArguments, UInt8ListReachEnd)
{
    list_test<uint8_t>({3, 2, 3, 6, 2, 'C'}, true, false);
}


//
// int16_t
//
TEST(TestArguments, Int16)
{
    value_test<int16_t>(3667, 11);
}

TEST(TestArguments, Int16Max)
{
    max_test<int16_t>(false);
}

TEST(TestArguments, Int16Vector)
{
    vector_test<int16_t>({3, 2, 3, 6, 2, -3}, false);
}

TEST(TestArguments, Int16VectorReachEnd)
{
    vector_test<int16_t>({3, 2, 3, 6, 2, -3}, true, false);
}

TEST(TestArguments, Int16List)
{
    list_test<int16_t>({3, 2, 3, 6, 2, -3}, false);
}

TEST(TestArguments, Int16ListReachEnd)
{
    list_test<int16_t>({3, 2, 3, 6, 2, -3}, true, false);
}


//
// uint16_t
//
TEST(TestArguments, UInt16)
{
    value_test<uint16_t>(3667u, 22u);
}

TEST(TestArguments, UInt16Vector)
{
    vector_test<uint16_t>({3, 2, 3, 6, 2, 66}, false);
}

TEST(TestArguments, UInt16VectorReachEnd)
{
    vector_test<uint16_t>({3, 2, 3, 6, 2, 66}, true, false);
}

TEST(TestArguments, UInt16List)
{
    list_test<uint16_t>({3, 2, 3, 6, 2, 66}, false);
}

TEST(TestArguments, UInt16ListReachEnd)
{
    list_test<uint16_t>({3, 2, 3, 6, 2, 66}, true, false);
}


//
// int32_t
//
TEST(TestArguments, Int32t)
{
    value_test<int32_t>(36673316, -1);
}

TEST(TestArguments, Int32Max)
{
    max_test<int32_t>(false);
}

TEST(TestArguments, Int32MaxOutOfRange)
{
    max_test<int32_t>(true);
}

TEST(TestArguments, Int32tVector)
{
    vector_test<int32_t>({3, 2, 3, 6, 2, 0}, false);
}

TEST(TestArguments, Int32tVectorReachEnd)
{
    vector_test<int32_t>({3, 2, 3, 6, 2, 0}, true, false);
}

TEST(TestArguments, Int32List)
{
    list_test<int32_t>({3, 2, 3, 6, 2, 0}, false);
}

TEST(TestArguments, Int32ListReachEnd)
{
    list_test<int32_t>({3, 2, 3, 6, 2, 0}, true, false);
}


//
// uint32_t
//
TEST(TestArguments, UInt32t)
{
    value_test<uint32_t>(36673316u, 634u);
}

TEST(TestArguments, UInt64Max)
{
    max_test<uint64_t>(false);
}

TEST(TestArguments, UInt64MaxOutOfRange)
{
    max_test<uint64_t>(true);
}

TEST(TestArguments, UInt32tVector)
{
    vector_test<uint32_t>({3, 2, 3, 6, 2, 111111}, false);
}

TEST(TestArguments, UInt32tVectorReachEnd)
{
    vector_test<uint32_t>({3, 2, 3, 6, 2, 1111111}, true, false);
}

TEST(TestArguments, UInt32List)
{
    list_test<uint32_t>({3, 2, 3, 6, 2, 1111111}, false);
}

TEST(TestArguments, UInt32ListReachEnd)
{
    list_test<uint32_t>({3, 2, 3, 6, 2, 1111111}, true, false);
}


//
// int64_t
//
TEST(TestArguments, Int64t)
{
    value_test<int64_t>(151651613, -1516);
}

TEST(TestArguments, Int64Max)
{
    max_test<int64_t>(false);
}

TEST(TestArguments, Int64MaxOutOfRange)
{
    max_test<int64_t>(true);
}

TEST(TestArguments, Int64tVector)
{
    vector_test<int64_t>({3, 2, 3, 6, 2, 151651613}, false);
}

TEST(TestArguments, Int64tVectorReachEnd)
{
    vector_test<int64_t>({3, 2, 3, 6, 2, 151651613}, true, false);
}

TEST(TestArguments, Int64List)
{
    list_test<int64_t>({3, 2, 3, 6, 2, 151651613}, false);
}

TEST(TestArguments, Int64ListReachEnd)
{
    list_test<int64_t>({3, 2, 3, 6, 2, 151651613}, true, false);
}


//
// uint64_t
//
TEST(TestArguments, UInt64t)
{
    value_test<uint64_t>(151651613u, 1516u);
}

TEST(TestArguments, UInt64tVector)
{
    vector_test<uint64_t>({3, 2, 3, 6, 2, 151651613u}, false);
}

TEST(TestArguments, UInt64tVectorReachEnd)
{
    vector_test<uint64_t>({3, 2, 3, 6, 2, 151651613u}, true, false);
}

TEST(TestArguments, UInt64List)
{
    list_test<uint64_t>({3, 2, 3, 6, 2, 151651613u}, false);
}

TEST(TestArguments, UInt64ListReachEnd)
{
    list_test<uint64_t>({3, 2, 3, 6, 2, 151651613u}, true, false);
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

TEST(TestArguments, IntList)
{
    list_test<int>({3, 2, 3, 6, 2, 2151112}, false);
}

TEST(TestArguments, IntListReachEnd)
{
    list_test<int>({3, 2, 3, 6, 2, 2151112}, true);
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

TEST(TestArguments, UnsignedIntVector)
{
    vector_test<unsigned int>({3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, false);
}

TEST(TestArguments, UnsignedIntVectorReachEnd)
{
    vector_test<unsigned int>({3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, true);
}

TEST(TestArguments, UnsignedIntList)
{
    list_test<unsigned int>({3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, false);
}

TEST(TestArguments, UnsignedIntListReachEnd)
{
    list_test<unsigned int>({3u, 2u, 34u, 6u, 2u, 100u, 2151112u}, true, false);
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

TEST(TestArguments, LongVector)
{
    vector_test<long>({3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, false);
}

TEST(TestArguments, LongVectorReachEnd)
{
    vector_test<long>({3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, true);
}

TEST(TestArguments, LongList)
{
    list_test<long>({3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, false);
}

TEST(TestArguments, LongListReachEnd)
{
    list_test<long>({3l, 2l, 34l, 6l, 2l, 100l, 2151112l}, true, false);
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

TEST(TestArguments, UnsignedLongVector)
{
    vector_test<unsigned long>({3ul, 2ul, 34ul, 6ul, 2ul, 100ul, 2151112ul}, false);
}

TEST(TestArguments, UnsignedLongVectorReachEnd)
{
    vector_test<unsigned long>({3ul, 2ul, 34ul, 6ul, 2l, 100ul, 2151112ul}, true);
}

TEST(TestArguments, UnsignedLongList)
{
    list_test<unsigned long>({3ul, 2ul, 34ul, 6ul, 2l, 100ul, 2151112ul}, false);
}

TEST(TestArguments, UnsignedLongListReachEnd)
{
    list_test<unsigned long>({3ul, 2ul, 34ul, 6ul, 2l, 100ul, 2151112ul}, true, false);
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

TEST(TestArguments, LongLongVector)
{
    vector_test<long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, false);
}

TEST(TestArguments, LongLongVectorReachEnd)
{
    vector_test<long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, true);
}

TEST(TestArguments, LongLongList)
{
    list_test<long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, false);
}

TEST(TestArguments, LongLongListReachEnd)
{
    list_test<long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, true, false);
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

TEST(TestArguments, UnsignedLongLongVector)
{
    vector_test<unsigned long long>({3ull, 2ull, 34ull, 6ull, 2ull, 100ull, 2151112ull}, false);
}

TEST(TestArguments, UnsignedLongLongVectorReachEnd)
{
    vector_test<unsigned long long>({3ull, 2ull, 34ull, 6ull, 2ull, 100ull, 2151112ull}, true);
}

TEST(TestArguments, UnsignedLongLongList)
{
    list_test<unsigned long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, false);
}

TEST(TestArguments, UnsignedLongLongListReachEnd)
{
    list_test<unsigned long long>({3ll, 2ll, 34ll, 6ll, 2ll, 100ll, 2151112ll}, true, false);
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

TEST(TestArguments, FloatVector)
{
    vector_test<float>({3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151.1112f}, false);
}

TEST(TestArguments, FloatVectorReachEnd)
{
    vector_test<float>({3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151.1112f}, true);
}

TEST(TestArguments, FloatList)
{
    list_test<float>({3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151.1112f}, false);
}

TEST(TestArguments, FloatListReachEnd)
{
    list_test<float>({3.2f, 2.0f, 34.0f, 6.0f, 2.0f, 100.0f, 2151.1112f}, true, false);
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

TEST(TestArguments, DoubleVector)
{
    vector_test<double>({3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151.1112}, false);
}

TEST(TestArguments, DoubleVectorReachEnd)
{
    vector_test<double>({3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151.1112}, true);
}

TEST(TestArguments, DoubleList)
{
    list_test<float>({3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151.1112}, false);
}

TEST(TestArguments, DoubleListReachEnd)
{
    list_test<float>({3.2, 2.0, 34.0, 6.0, 2.0, 100.0, 2151.1112}, true, false);
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

TEST(TestArguments, LongDoubleVector)
{
    vector_test<long double>({3.2l, 2.0l, 34.0l, 6.0l, 2.0l, 100.0l, 2151.1112l}, false);
}

TEST(TestArguments, LongDoubleVectorReachEnd)
{
    vector_test<long double>({3.2l, 2.0l, 34.0l, 6.0l, 2.0l, 100.0l, 2151.1112l}, true);
}

TEST(TestArguments, LongDoubleList)
{
    list_test<long double>({3.2l, 2.0l, 34.0l, 6.0l, 2.0l, 100.0l, 2151.1112l}, false);
}

TEST(TestArguments, LongDoubleListReachEnd)
{
    list_test<long double>({3.2l, 2.0l, 34.0l, 6.0l, 2.0l, 100.0l, 2151.1112l}, true, false);
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

TEST(TestArguments, StringVector)
{
    vector_test<std::string>({"THIS", "IS", "SAMPLE", "TEXT"}, false);
}

TEST(TestArguments, StringVectorReachEnd)
{
    vector_test<std::string>({"THIS", "IS", "SAMPLE", "TEXT"}, true, false);
}

TEST(TestArguments, StringList)
{
    list_test<std::string>({"THIS", "IS", "SAMPLE", "TEXT"}, false);
}

TEST(TestArguments, StringListReachEnd)
{
    list_test<std::string>({"THIS", "IS", "SAMPLE", "TEXT"}, true, false);
}
