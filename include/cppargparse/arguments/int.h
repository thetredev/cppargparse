#ifndef CPPARGPARSE_ARGUMENTS_INT_H
#define CPPARGPARSE_ARGUMENTS_INT_H

#include <algorithm>
#include <sstream>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"


namespace cppargparse {


template <>
/**
 * @brief The type_trait struct for the integer type.
 */
struct argument<int>
{
    /**
     * @brief Try to parse a command line argument as an int. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The int value of the command line argument next in line on success or throw a #parser::ParserException on failure.
     */
    static int parse(const types::CommandLineArgument_t &cmdarg)
    {
        return convert(std::next(cmdarg));
    }

    /**
     * @brief Try to convert a command line argument to an int value. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The int value of the command line argument on success or throw a #parser::ParserException on failure.
     */
    static int convert(const types::CommandLineArgument_t &cmdarg)
    {
        try
        {
            return std::stoi(*cmdarg);
        }

        catch (std::invalid_argument const &)
        {
            throw errors::CommandLineOptionError(error_message(cmdarg));
        }
        catch (std::out_of_range const &)
        {
            throw errors::CommandLineOptionError(error_message(cmdarg));
        }
    }

    /**
     * @brief Generate an error message for a value that's not an int.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return An error message for a value that's not an int.
     */
    static const char *error_message(const types::CommandLineArgument_t &cmdarg)
    {
        std::ostringstream message;
        message << "Couldn't parse '" << *cmdarg << "' as an integer.";

        return message.str().c_str();
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_INT_H
