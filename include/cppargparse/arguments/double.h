#ifndef CPPARGPARSE_ARGUMENTS_DOUBLE_H
#define CPPARGPARSE_ARGUMENTS_DOUBLE_H

#include <algorithm>
#include <sstream>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"


namespace cppargparse {


template <>
/**
 * @brief The type_trait struct for the double type.
 */
struct argument<double>
{
    /**
     * @brief Try to parse a command line argument as a double. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The double value of the command line argument next in line on success or throw a #parser::ParserException on failure.
     */
    static double parse(const types::CommandLineArgument_t &cmarg)
    {
        return convert(std::next(cmarg));
    }


    /**
     * @brief Try to convert a command line argument to a double value. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The double value of the command line argument on success or throw a #parser::ParserException on failure.
     */
    static double convert(const types::CommandLineArgument_t &cmdarg)
    {
        try
        {
            return std::stod(*cmdarg);
        }

        catch (std::invalid_argument const &)
        {
            throw errors::ParserError(error_message(cmdarg));
        }
        catch (std::out_of_range const &)
        {
            throw errors::ParserError(error_message(cmdarg));
        }
    }

    /**
     * @brief Generate an error message for a value that's not a double.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return An error message for a value that's not a double.
     */
    static const char *error_message(const types::CommandLineArgument_t &cmdarg)
    {
        std::ostringstream message;
        message << "Couldn't parse '" << *cmdarg << "' as a double value.";

        return message.str().c_str();
    }
};


template <>
/**
 * @brief The type_trait struct for the long double type.
 */
struct argument<long double>
{
    /**
     * @brief Try to parse a command line argument as a long double. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The long double value of the command line argument next in line on success or throw a #parser::ParserException on failure.
     */
    static long double parse(const types::CommandLineArgument_t &cmdarg)
    {
        return convert(std::next(cmdarg));
    }

    /**
     * @brief Try to convert a command line argument to a long double value. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The long double value of the command line argument on success or throw a #parser::ParserException on failure.
     */
    static long double convert(const types::CommandLineArgument_t &cmdarg)
    {
        try
        {
            return std::stold(*cmdarg);
        }

        catch (std::invalid_argument const &)
        {
            throw errors::ParserError(error_message(cmdarg));
        }
        catch (std::out_of_range const &)
        {
            throw errors::ParserError(error_message(cmdarg));
        }
    }

    /**
     * @brief Generate an error message for a value that's not a long double.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return An error message for a value that's not a long double.
     */
    static const char *error_message(const types::CommandLineArgument_t &cmdarg)
    {
        std::ostringstream message;
        message << "Couldn't parse '" << *cmdarg << "' as a long double value.";

        return message.str().c_str();
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_DOUBLE_H
