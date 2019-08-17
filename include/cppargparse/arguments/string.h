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
     * @param position The command line argument iterator.
     * @param cmdargs The command line arguments.
     *
     * @return The std::string value of the command line argument next in line.
     */
    static const std::string parse(
            const types::CommandLine_t &cmd,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &cmdargs)
    {
        return convert(cmd, std::next(position), cmdargs);
    }

    /**
     * @brief Try to convert a command line argument to a std::string.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The std::string value of the command line argument.
     * @throws #cppargparse::errors::CommandLineOptionError if there is no value to parse.
     */
    static const std::string convert(
            const types::CommandLine_t &cmd,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        if (position == cmd.cend())
        {
            throw errors::CommandLineOptionError(error_message(position));
        }

        return *position;
    }

    /**
     * @brief Generate an error message for a value that's not a std::string.
     *
     * @param position The command line argument iterator.
     *
     * @return An error message for a value that's not a std::string.
     */
    static const char *error_message(const types::CommandLinePosition_t &position)
    {
        std::ostringstream message;
        message << "Couldn't convert " << *position << "to type <std::string>.";

        return message.str().c_str();
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_STRING_H
