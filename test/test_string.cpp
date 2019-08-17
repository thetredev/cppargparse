#include <string>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestString, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_string_required"
    );


    // Add arguments
    const auto x = arg_parser.add_arg("-x");
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");
    const auto c = arg_parser.add_arg("-c");
    const auto output = arg_parser.add_arg("--output");


    // Test cmdarg: -x
    // is a flag, so -a is the parsed argument value
    const std::string x_value = arg_parser.get_option<std::string>(x);
    EXPECT_EQ("-a", x_value);


    // Test cmdarg: -a
    const std::string a_value = arg_parser.get_option<std::string>(a);
    EXPECT_EQ("4", a_value);

    // Test cmdarg: -b
    const std::string b_value = arg_parser.get_option<std::string>(b);
    EXPECT_EQ("-150", b_value);

    // Test cmdarg: -c
    const std::string c_value = arg_parser.get_option<std::string>(c);
    EXPECT_EQ("THIS", c_value);

    // Test cmdarg: --output
    const std::string output_value = arg_parser.get_option<std::string>(output);
    EXPECT_EQ("/tmp/testfile", output_value);
}


TEST(TestString, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_string_optional"
    );


    // Add arguments
    const auto x = arg_parser.add_arg("-x");
    const auto a = arg_parser.add_arg("-a");
    const auto b = arg_parser.add_arg("-b");
    const auto c = arg_parser.add_arg("-c");
    const auto output = arg_parser.add_arg("--output");


    // Test cmdarg: -x
    // with a default value "DEFAULT"
    const std::string x_value = arg_parser.get_option<std::string>(x, "DEFAULT");

    // -x is a flag, so "-a" is the parsed argument value
    EXPECT_EQ("-a", x_value);


    // Test cmdarg: -a
    // with a default value "DEFAULT"
    const std::string a_value = arg_parser.get_option<std::string>(a, "DEFAULT");
    EXPECT_EQ("4", a_value);

    // Test cmdarg: -b
    // with a default value "DEFAULT"
    const std::string b_value = arg_parser.get_option<std::string>(b, "DEFAULT");
    EXPECT_EQ("-150", b_value);


    // Test cmdarg: -c
    // with a default value "cccccccccc"
    const std::string c_value = arg_parser.get_option<std::string>(c, "cccccccccc");
    EXPECT_EQ("THIS", c_value);

    // Test cmdarg: --output
    // with a default value "/"
    const std::string output_value = arg_parser.get_option<std::string>(output, "/");
    EXPECT_EQ("/tmp/testfile", output_value);
}
