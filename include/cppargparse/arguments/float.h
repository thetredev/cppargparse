#ifndef CPPARGPARSE_ARGUMENTS_FLOAT_H
#define CPPARGPARSE_ARGUMENTS_FLOAT_H

#include <algorithm>
#include <sstream>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"


namespace cppargparse {


template <>
/**
 * @brief The type_trait struct for the float type.
 */
struct argument<float>
{
    /**
     * @brief Try to parse a command line argument as a float. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The float value of the command line argument next in line on success or throw a #parser::ParserException on failure.
     */
    static float parse(const types::CommandLineArgument_t &key_it)
    {
        return convert(std::next(key_it));
    }

    /**
     * @brief Try to convert a command line argument to a float value. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The float value of the command line argument on success or throw a #parser::ParserException on failure.
     */
    static float convert(const types::CommandLineArgument_t &value_it)
    {
        try
        {
            return std::stof(*value_it);
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
     * @brief Generate an error message for a value that's not a float.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return An error message for a value that's not a float.
     */
    static const char *error_message(const types::CommandLineArgument_t &value_it)
    {
        std::ostringstream message;
        message << "Couldn't parse '" << *value_it << "' as a float value.";

        return message.str().c_str();
    }
};

} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_FLOAT_H
