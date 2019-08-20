#ifndef CPPARGPARSE_TEST_UTILS_H
#define CPPARGPARSE_TEST_UTILS_H

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


cppargparse::parser::ArgumentParser parse_cmdargs(const std::string &command_line, const std::string &application_description)
{
    std::vector<std::string> command_line_tokens = get_cmdargs(command_line);

    std::vector<char *> char_tokens;
    std::transform(command_line_tokens.begin(), command_line_tokens.end(), std::back_inserter(char_tokens), get_cmd_chars);

    return cppargparse::parser::ArgumentParser(
                static_cast<int>(char_tokens.size()), char_tokens.data(), application_description
    );
}


} // namespace cppargparse::test

#endif // CPPARGPARSE_TEST_UTILS_H
