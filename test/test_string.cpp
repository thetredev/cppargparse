#include <map>
#include <vector>

#include <gtest/gtest.h>

#include <cppargparse/cppargparse.h>
#include <cppargparse/errors.h>

#include "test_common.h"


TEST(TestString, ArgumentNotPassed)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test cmdarg: --some-unused-arg
    // which has not been passed
    EXPECT_THROW(parser::parse_arg<int>("--some-unused-arg"), errors::CommandLineArgumentError);
}


TEST(TestString, Required)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test cmdarg: -x
    // is a flag, so -a is the parsed argument value
    std::string x = parser::parse_arg<std::string>("-x");
    EXPECT_EQ("-a", x);


    // Test cmdarg: -a
    const std::string a = parser::parse_arg<std::string>("-a");
    EXPECT_EQ("4", a);

    // Test cmdarg: -b
    const std::string b = parser::parse_arg<std::string>("-b");
    EXPECT_EQ("-150", b);

    // Test cmdarg: -c
    const std::string c = parser::parse_arg<std::string>("-c");
    EXPECT_EQ("THIS", c);

    // Test cmdarg: --output
    const std::string output = parser::parse_arg<std::string>("--output");
    EXPECT_EQ("/tmp/testfile", output);
}


TEST(TestString, Optional)
{
    // Parse the command line arguments
    using namespace cppargparse;
    test::parse_cmdargs("-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile");


    // Test cmdarg: -x
    // with a default value "DEFAULT"
    std::string x = parser::parse_arg<std::string>("-x", "DEFAULT");

    // -x is a flag, so "-a" is the parsed argument value
    EXPECT_EQ("-a", x);


    // Test cmdarg: -y
    // with a default value "DEFAULT"
    std::string y = parser::parse_arg<std::string>("-y", "DEFAULT");
    EXPECT_EQ("DEFAULT", y);

    // Test cmdarg: -a
    // with a default value "DEFAULT"
    const std::string a = parser::parse_arg<std::string>("-a", "DEFAULT");
    EXPECT_EQ("4", a);

    // Test cmdarg: -b
    // with a default value "DEFAULT"
    const std::string b = parser::parse_arg<std::string>("-b", "DEFAULT");
    EXPECT_EQ("-150", b);


    // Test cmdarg: -c
    // with a default value "cccccccccc"
    const std::string c = parser::parse_arg<std::string>("-c", "cccccccccc");
    EXPECT_EQ("THIS", c);

    // Test cmdarg: --output
    // with a default value "/"
    const std::string output = parser::parse_arg<std::string>("--output", "/");
    EXPECT_EQ("/tmp/testfile", output);


    // Test cmdarg: --dir
    // with a default value "/home/default"
    std::string dir = parser::parse_arg<std::string>("--dir", "/home/default");
    EXPECT_EQ("/home/default", dir);
}
