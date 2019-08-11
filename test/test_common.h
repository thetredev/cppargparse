#ifndef CPPARGPARSE_TEST_UTILS_H
#define CPPARGPARSE_TEST_UTILS_H

#include <iterator>
#include <string>
#include <vector>


#include <cppargparse/cppargparse.h>


namespace cppargparse::test {


// Simulate the command line arguments passed to the program
const std::string command_line = "-t -x -a 4 -b -150 -c THIS SHOULD RAISE AN ERROR --output /tmp/testfile";



std::vector<std::string> get_cmdargs(const std::string &command_line)
{
    std::istringstream tokens(command_line);

    return {
        std::istream_iterator<std::string> {tokens},
        std::istream_iterator<std::string> {}
    };
}


void get_char_cmdargs(std::vector<std::string> command_line_tokens, std::vector<const char *> &char_tokens)
{
    for (const auto &token : command_line_tokens)
    {
        char_tokens.emplace_back(token.c_str());
    }
}


void parse_cmdargs()
{
    std::vector<std::string> command_line_tokens = get_cmdargs(test::command_line);

    std::vector<const char *> char_tokens;
    test::get_char_cmdargs(command_line_tokens, char_tokens);

    algorithm::collect_cmdargs(char_tokens.size(), char_tokens.data());
}


} // namespace cppargparse::test

#endif // CPPARGPARSE_TEST_UTILS_H
