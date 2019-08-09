#ifndef CPPARGPARSE_ARGUMENTS_DOUBLE_H
#define CPPARGPARSE_ARGUMENTS_DOUBLE_H

#include <algorithm>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"
#include "numerical.h"


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
    static double parse(const types::CommandLineArgument_t &cmdarg)
    {
        return numerical_argument::parse<double>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stod), "double");
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
        return numerical_argument::convert<double>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stod), "double");
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
        return numerical_argument::parse<double>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stold), "long double");
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
        return numerical_argument::convert<double>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stold), "long double");
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_DOUBLE_H
