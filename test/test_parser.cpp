#include <gtest/gtest.h>

#define private public
#include <cppargparse/cppargparse.h>
#undef protected

#include "test_common.h"


//
// Constructor
//
TEST(TestParser, Constructor)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 3"), "TestParser");

    ASSERT_EQ(size_t(2), arg_parser.m_cmd.size());
    ASSERT_EQ(size_t(0), arg_parser.m_cmdargs.size());
}


//
// add_arg() 1
//
TEST(TestParser, AddArg1)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 3"), "TestParser");

    const cmd::CommandLineArgument arg {
        "-t", "--time", std::string(), arg_parser.m_cmd.cbegin()
    };

    arg_parser.add_arg(arg);

    ASSERT_EQ(size_t(2), arg_parser.m_cmd.size());
    ASSERT_EQ(size_t(1), arg_parser.m_cmdargs.size());

    ASSERT_EQ("-t", arg.id());
    ASSERT_EQ("--time", arg.id_alt());
    ASSERT_EQ(std::string(), arg.description());
    ASSERT_EQ(arg_parser.m_cmd.cbegin(), arg.position());
}


//
// add_arg() 2
//
TEST(TestParser, AddArg2)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 3"), "TestParser");

    const auto arg = arg_parser.add_arg("-t");

    ASSERT_EQ(size_t(2), arg_parser.m_cmd.size());
    ASSERT_EQ(size_t(1), arg_parser.m_cmdargs.size());

    ASSERT_EQ("-t", arg.id());
    ASSERT_EQ(std::string(), arg.id_alt());
    ASSERT_EQ(std::string(), arg.description());
    ASSERT_EQ(arg_parser.m_cmd.cbegin(), arg.position());
}


//
// add_arg() 3
//
TEST(TestParser, AddArg3)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 3"), "TestParser");

    const auto arg = arg_parser.add_arg("-t", "--time");

    ASSERT_EQ(size_t(2), arg_parser.m_cmd.size());
    ASSERT_EQ(size_t(1), arg_parser.m_cmdargs.size());

    ASSERT_EQ("-t", arg.id());
    ASSERT_EQ("--time", arg.id_alt());
    ASSERT_EQ(std::string(), arg.description());
    ASSERT_EQ(arg_parser.m_cmd.cbegin(), arg.position());
}


//
// add_arg() 4
//
TEST(TestParser, AddArg4)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 3"), "TestParser");

    const auto arg = arg_parser.add_arg("-t", "--time", "The time to wait for X to happen.");

    ASSERT_EQ(size_t(2), arg_parser.m_cmd.size());
    ASSERT_EQ(size_t(1), arg_parser.m_cmdargs.size());

    ASSERT_EQ("-t", arg.id());
    ASSERT_EQ("--time", arg.id_alt());
    ASSERT_EQ("The time to wait for X to happen.", arg.description());
    ASSERT_EQ(arg_parser.m_cmd.cbegin(), arg.position());
}


//
// add_help()
//
TEST(TestParser, AddHelp)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 3"), "TestParser");

    const auto help = arg_parser.add_help();

    ASSERT_EQ(size_t(2), arg_parser.m_cmd.size());
    ASSERT_EQ(size_t(1), arg_parser.m_cmdargs.size());

    ASSERT_EQ("-h", help.id());
    ASSERT_EQ("--help", help.id_alt());
    ASSERT_EQ("Display this information", help.description());
    ASSERT_EQ(arg_parser.m_cmd.cend(), help.position());
}


//
// get_flag() 1
//
TEST(TestParser, GetFlag1)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 3"), "TestParser");

    const auto arg = arg_parser.add_help();
    ASSERT_FALSE(arg_parser.get_flag(arg));
}


//
// get_flag() 2
//
TEST(TestParser, GetFlag2)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("--help"), "TestParser");

    const auto arg = arg_parser.add_help();
    ASSERT_TRUE(arg_parser.get_flag(arg));
}


//
// get_option() 1
//
TEST(TestParser, GetOption1)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 60"), "TestParser");

    const auto arg = arg_parser.add_arg("-t", "--time", "The time...");
    ASSERT_EQ(60, arg_parser.get_option<int>(arg));
}


//
// get_option() 2 (error)
//
TEST(TestParser, GetOption2)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 60"), "TestParser");

    const auto arg = arg_parser.add_arg("-f", "--frozen", "Frozen state");
    ASSERT_THROW(arg_parser.get_option<int>(arg), errors::CommandLineArgumentError);
}


//
// get_option() 3 (default)
//
TEST(TestParser, GetOption3)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-f 60"), "TestParser");

    const auto arg = arg_parser.add_arg("-f", "--frozen", "Frozen state");
    ASSERT_EQ(60, arg_parser.get_option<int>(arg, 40));
}


//
// get_option() 4 (default value returned)
//
TEST(TestParser, GetOption4)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 60"), "TestParser");

    const auto arg = arg_parser.add_arg("-f", "--frozen", "Frozen state");
    ASSERT_EQ(40, arg_parser.get_option<int>(arg, 40));
}



//
// ----- Callback API -----
//


// Usage callback
void usage_callback(const cppargparse::parser::ArgumentParser &arg_parser)
{
    ASSERT_NE(0, arg_parser.m_cmdargs.size());
}



//
// add_flag_with_callback() 1
//
TEST(TestParser, AddFlagWithCallback1)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-h"), "TestParser");

    arg_parser.with_flag("-h", &usage_callback);
    arg_parser.with_flag("--help", &usage_callback);
}


//
// add_flag_with_callback() 2
//
TEST(TestParser, AddFlagWithCallback2)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-h"), "TestParser");

    arg_parser.with_flag("-h", "--help", &usage_callback);
    arg_parser.with_flag("-t", "--test", &usage_callback);
}


//
// add_flag_with_callback() 3
//
TEST(TestParser, AddFlagWithCallback3)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-h"), "TestParser");

    arg_parser.with_flag("-h", "--help", "Help information", &usage_callback);
    arg_parser.with_flag("-t", "--test", "Invalid flag", &usage_callback);
}


//
// add_help_with_callback() 1
//
TEST(TestParser, AddHelpWithCallback1)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-h"), "TestParser");

    arg_parser.with_help(&usage_callback);
}


//
// add_help_with_callback() 2
//
TEST(TestParser, AddHelpWithCallback2)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t"), "TestParser");

    arg_parser.with_help(&usage_callback);
}



// Callback for checking if -t is 4 (integer)
void check_t_is_4(const cppargparse::parser::ArgumentParser &, int value)
{
    ASSERT_EQ(4, value);
}



//
// add_arg_with_callback() 1
//
TEST(TestParser, AddArgWithCallback1)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 4 -x"), "TestParser");

    arg_parser.with<int>("-t", &check_t_is_4);

    ASSERT_THROW(arg_parser.with<int>("-p", &check_t_is_4), errors::CommandLineArgumentError);
    ASSERT_THROW(arg_parser.with<int>("-x", &check_t_is_4), errors::CommandLineOptionError);
}


//
// add_arg_with_callback() 2
//
TEST(TestParser, AddArgWithCallback2)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 4 -x"), "TestParser");

    arg_parser.with<int>("-t", "--time", &check_t_is_4);

    ASSERT_THROW(arg_parser.with<int>("-p", "--productnum", &check_t_is_4), errors::CommandLineArgumentError);
    ASSERT_THROW(arg_parser.with<int>("-x", "--existence", &check_t_is_4), errors::CommandLineOptionError);
}


//
// add_arg_with_callback() 3
//
TEST(TestParser, AddArgWithCallback3)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t 4 -x"), "TestParser");

    arg_parser.with<int>("-t", "--time", "The time it takes for...", &check_t_is_4);

    ASSERT_THROW(arg_parser.with<int>("-p", "--productnum", "Some product number", &check_t_is_4), errors::CommandLineArgumentError);
    ASSERT_THROW(arg_parser.with<int>("-x", "--existence", "Some philosophical description", &check_t_is_4), errors::CommandLineOptionError);
}


//
// add_arg_with_callback_default() 1
//
TEST(TestParser, AddArgWithCallbackDefault1)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t -x"), "TestParser");

    arg_parser.with_default<int>("-t", 4, &check_t_is_4);
}


//
// add_arg_with_callback_default() 2
//
TEST(TestParser, AddArgWithCallbackDefault2)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t -x"), "TestParser");

    arg_parser.with_default<int>("-t", "--time", 4, &check_t_is_4);
}


//
// add_arg_with_callback_default() 3
//
TEST(TestParser, AddArgWithCallbackDefault3)
{
    using namespace cppargparse;
    auto arg_parser = test::make_arg_parser(test::parse_cmdargs("-t -x"), "TestParser");

    arg_parser.with_default<int>("-t", "--time", "The time it takes for...", 4, &check_t_is_4);
}
