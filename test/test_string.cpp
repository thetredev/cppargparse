#include <string>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>

#include "test_common.h"


TEST(TestString, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_string_argument_not_passed"
    );


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(arg_parser.get_option<std::string>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestString, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = test::parse_cmdargs(
                "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile",
                "test_string_required"
    );


    // Add arguments
    arg_parser.add_arg("-x");
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");
    arg_parser.add_arg("-c");
    arg_parser.add_arg("--output");


    // Test cmdarg: -x
    // is a flag, so -a is the parsed argument value
    const std::string x = arg_parser.get_option<std::string>("-x");
    EXPECT_EQ("-a", x);


    // Test cmdarg: -a
    const std::string a = arg_parser.get_option<std::string>("-a");
    EXPECT_EQ("4", a);

    // Test cmdarg: -b
    const std::string b = arg_parser.get_option<std::string>("-b");
    EXPECT_EQ("-150", b);

    // Test cmdarg: -c
    const std::string c = arg_parser.get_option<std::string>("-c");
    EXPECT_EQ("THIS", c);

    // Test cmdarg: --output
    const std::string output = arg_parser.get_option<std::string>("--output");
    EXPECT_EQ("/tmp/testfile", output);
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
    arg_parser.add_arg("-x");
    arg_parser.add_arg("-a");
    arg_parser.add_arg("-b");
    arg_parser.add_arg("-c");
    arg_parser.add_arg("--output");


    // Test cmdarg: -x
    // with a default value "DEFAULT"
    const std::string x = arg_parser.get_option<std::string>("-x", "DEFAULT");

    // -x is a flag, so "-a" is the parsed argument value
    EXPECT_EQ("-a", x);


    // Test cmdarg: -y
    // with a default value "DEFAULT"
    const std::string y = arg_parser.get_option<std::string>("-y", "DEFAULT");
    EXPECT_EQ("DEFAULT", y);

    // Test cmdarg: -a
    // with a default value "DEFAULT"
    const std::string a = arg_parser.get_option<std::string>("-a", "DEFAULT");
    EXPECT_EQ("4", a);

    // Test cmdarg: -b
    // with a default value "DEFAULT"
    const std::string b = arg_parser.get_option<std::string>("-b", "DEFAULT");
    EXPECT_EQ("-150", b);


    // Test cmdarg: -c
    // with a default value "cccccccccc"
    const std::string c = arg_parser.get_option<std::string>("-c", "cccccccccc");
    EXPECT_EQ("THIS", c);

    // Test cmdarg: --output
    // with a default value "/"
    const std::string output = arg_parser.get_option<std::string>("--output", "/");
    EXPECT_EQ("/tmp/testfile", output);


    // Test cmdarg: --dir
    // with a default value "/home/default"
    const std::string dir = arg_parser.get_option<std::string>("--dir", "/home/default");
    EXPECT_EQ("/home/default", dir);
}
