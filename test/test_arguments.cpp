#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


//
// int
//
TEST(TestArguments, Int)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(3, arg_parser.get_option<int>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(5, arg_parser.get_option<int>(x, 5));
}

//
// vector of ints
//
TEST(TestArguments, VectorOfInts)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<int> seq_values = arg_parser.get_option<std::vector<int>>(seq);

    const std::vector<int> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of ints reach end
//
TEST(TestArguments, VectorOfIntsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<int> seq_values = arg_parser.get_option<std::vector<int>>(seq);

    const std::vector<int> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// unsigned int
//
TEST(TestArguments, UnsignedInt)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(3, arg_parser.get_option<unsigned int>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(5, arg_parser.get_option<unsigned int>(x, 5));
}

//
// unsigned int out of range
//
TEST(TestArguments, UnsignedIntOutOfRange)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 42949672953333", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_THROW(arg_parser.get_option<unsigned int>(t), errors::CommandLineOptionError);

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(5, arg_parser.get_option<unsigned int>(x, 5));
}

//
// vector of unsigned ints
//
TEST(TestArguments, VectorOfUnsignedInts)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<unsigned int> seq_values = arg_parser.get_option<std::vector<unsigned int>>(seq);

    const std::vector<unsigned int> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of unsigned ints reach end
//
TEST(TestArguments, VectorOfUnsignedIntsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<unsigned int> seq_values = arg_parser.get_option<std::vector<unsigned int>>(seq);

    const std::vector<unsigned int> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// long
//
TEST(TestArguments, Long)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(3, arg_parser.get_option<long>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(5, arg_parser.get_option<long>(x, 5));
}

//
// vector of longs
//
TEST(TestArguments, VectorOfLongs)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<long> seq_values = arg_parser.get_option<std::vector<long>>(seq);

    const std::vector<long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of longs reach end
//
TEST(TestArguments, VectorOfLongsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<long> seq_values = arg_parser.get_option<std::vector<long>>(seq);

    const std::vector<long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// long long
//
TEST(TestArguments, LongLong)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(3, arg_parser.get_option<long long>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(5, arg_parser.get_option<long long>(x, 5));
}

//
// vector of long longs
//
TEST(TestArguments, VectorOfLongLongs)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<long long> seq_values = arg_parser.get_option<std::vector<long long>>(seq);

    const std::vector<long long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of long longs reach end
//
TEST(TestArguments, VectorOfLongLongsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<long long> seq_values = arg_parser.get_option<std::vector<long long>>(seq);

    const std::vector<long long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// unsigned long
//
TEST(TestArguments, UnsignedLong)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(3, arg_parser.get_option<unsigned long>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(5, arg_parser.get_option<unsigned long>(x, 5));
}

//
// vector of unsigned longs
//
TEST(TestArguments, VectorOfUnsignedLongs)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<unsigned long> seq_values = arg_parser.get_option<std::vector<unsigned long>>(seq);

    const std::vector<unsigned long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of unsigned longs reach end
//
TEST(TestArguments, VectorOfUnsignedLongsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<unsigned long> seq_values = arg_parser.get_option<std::vector<unsigned long>>(seq);

    const std::vector<unsigned long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}


//
// unsigned long long
//
TEST(TestArguments, UnsignedLongLong)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("-t 3", "TestArguments");

    const auto t = arg_parser.add_arg("-t");
    ASSERT_EQ(3, arg_parser.get_option<unsigned long long>(t));

    const auto x = arg_parser.add_arg("-x");
    ASSERT_EQ(5, arg_parser.get_option<unsigned long long>(x, 5));
}

//
// vector of unsigned long longs
//
TEST(TestArguments, VectorOfUnsignedLongLongs)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    const std::vector<unsigned long long> seq_values = arg_parser.get_option<std::vector<unsigned long long>>(seq);

    const std::vector<unsigned long long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
}

//
// vector of unsigned long longs reach end
//
TEST(TestArguments, VectorOfUnsignedLongLongsReachEnd)
{
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs("--seq 3 2 34 6 2 100 2151112 -t 3", "TestArguments");

    const auto seq = arg_parser.add_arg("-s", "--seq");
    arg_parser.add_arg("-t");

    const std::vector<unsigned long long> seq_values = arg_parser.get_option<std::vector<unsigned long long>>(seq);

    const std::vector<unsigned long long> seq_expected {
        3, 2, 34, 6, 2, 100, 2151112
    };


    for (size_t i = 0; i < seq_expected.size(); ++i)
    {
        ASSERT_EQ(seq_expected.at(i), seq_values.at(i));
    }
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
