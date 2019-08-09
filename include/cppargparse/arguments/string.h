#ifndef CPPARGPARSE_ARGUMENTS_STRING_H
#define CPPARGPARSE_ARGUMENTS_STRING_H

#include <algorithm>
#include <sstream>
#include <string>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"


namespace cppargparse {


template <>
/**
 * @brief The type_trait struct for the std::string type.
 */
struct argument<std::string>
{
    /**
     * @brief Try to parse a command line argument as a std::string. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The std::string value of the command line argument next in line on success or throw a #parser::ParserException on failure.
     */
    static const std::string parse(const types::CommandLineArgument_t &cmdarg)
    {
        return convert(std::next(cmdarg));
    }

    /**
     * @brief Try to convert a command line argument to a std::string. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The std::string value of the command line argument on success or throw a #parser::ParserException on failure.
     */
    static const std::string convert(const types::CommandLineArgument_t &cmdarg)
    {
        if (cmdarg == g_cmdargs.cend())
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
