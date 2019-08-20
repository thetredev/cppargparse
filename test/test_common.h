#ifndef CPPARGPARSE_TEST_COMMON_H
#define CPPARGPARSE_TEST_COMMON_H

#include <cstring>
#include <iterator>
#include <string>
#include <vector>

#include <cppargparse/cppargparse.h>


namespace cppargparse::test {


std::vector<std::string> get_cmdargs(const std::string &command_line)
{
    std::istringstream tokens(command_line);

    return {
        std::istream_iterator<std::string> {tokens},
        std::istream_iterator<std::string> {}
    };
}


char *get_cmd_chars(const std::string &token)
{
   char *chars = new char[token.size() + 1];
   std::strcpy(chars, token.c_str());

   return chars;
}


std::vector<char *> parse_cmdargs(const std::string &command_line)
{
    std::vector<std::string> command_line_tokens = get_cmdargs(command_line);

    std::vector<char *> char_tokens;
    std::transform(command_line_tokens.begin(), command_line_tokens.end(), std::back_inserter(char_tokens), get_cmd_chars);

    return char_tokens;
}


cppargparse::parser::ArgumentParser make_arg_parser(
                std::vector<char *> cmdargs,
                const std::string &application_description)
{
    const cppargparse::parser::ArgumentParser arg_parser(
                        static_cast<int>(cmdargs.size()),
                        const_cast<char **>(cmdargs.data()),
                        application_description);

    for (const char *cmdarg : cmdargs)
    {
        delete cmdarg;
    }

    return arg_parser;
}


} // namespace cppargparse::test

#endif // CPPARGPARSE_TEST_COMMON_H
