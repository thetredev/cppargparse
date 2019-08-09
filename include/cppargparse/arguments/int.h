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
     * @brief Try to parse and return the integer value for an argument. Throw a #parser::ParserException on failure.
     *
     * @param key_it The argument key iterator.
     *
     * @return The parsed integer value for an argument on success or throw a #parser::ParserException on failure.
     */
    static int parse(const types::CommandLineArgument_t &key_it)
    {
        return convert(std::next(key_it));
    }

    /**
     * @brief Try to convert and return the given argument value as an int. Throw a #parser::ParserException on failure.
     *
     * @param value_it The argument value iterator.
     *
     * @return The converted int value of an argument value on success or throw a #parser::ParserException on failure.
     */
    static int convert(const types::CommandLineArgument_t &value_it)
    {
        try
        {
            return std::stoi(*value_it);
        }

        catch (std::invalid_argument const &)
        {
            throw errors::CommandLineOptionError(error_message(value_it));
        }
        catch (std::out_of_range const &)
        {
            throw errors::CommandLineOptionError(error_message(value_it));
        }
    }

    /**
     * @brief Generate an error message for a value that's not an integer.
     *
     * @param value_it The argument value iterator.
     *
     * @return An error message for a value that's not an integer.
     */
    static const char *error_message(const types::CommandLineArgument_t &value_it)
    {
        std::ostringstream message;
        message << "Couldn't parse '" << *value_it << "' as an integer.";

        return message.str().c_str();
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_INT_H
