#ifndef CPPARGPARSE_ARGUMENTS_STRING_H
#define CPPARGPARSE_ARGUMENTS_STRING_H

#include <algorithm>
#include <sstream>
#include <string>

#include <cppargparse/errors.h>
#include <cppargparse/types.h>

#include "default.h"


namespace cppargparse {


template <>
/**
 * @brief The argument struct for the std::string type.
 */
struct argument<std::string>
{
    /**
     * @brief Try to parse a command line argument as a std::string.
     *
     * @param cmd The command line.
     * @param cmdarg The command line argument iterator.
     *
     * @return The std::string value of the command line argument next in line.
     */
    static const std::string parse(
            const types::CommandLine_t &cmd,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &cmdargs)
    {
        return convert(cmd, std::next(cmdarg), cmdargs);
    }

    /**
     * @brief Try to convert a command line argument to a std::string.
     *
     * @param cmd The command line.
     * @param cmdarg The command line argument iterator.
     *
     * @return The std::string value of the command line argument.
     * @throws #cppargparse::errors::CommandLineOptionError if there is no value to parse.
     */
    static const std::string convert(
            const types::CommandLine_t &cmd,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &)
    {
        if (cmdarg == cmd.cend())
        {
            throw errors::CommandLineOptionError(error_message(cmdarg));
        }

        return *cmdarg;
    }

    /**
     * @brief Generate an error message for a value that's not a std::string.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return An error message for a value that's not a std::string.
     */
    static const char *error_message(const types::CommandLineArgument_t &cmdarg)
    {
        std::ostringstream message;
        message << "Couldn't convert " << *cmdarg << "to type <std::string>.";

        return message.str().c_str();
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_STRING_H
