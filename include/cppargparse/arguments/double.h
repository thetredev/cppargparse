#ifndef CPPARGPARSE_ARGUMENTS_DOUBLE_H
#define CPPARGPARSE_ARGUMENTS_DOUBLE_H

#include <algorithm>

#include <cppargparse/types.h>

#include "default.h"
#include "numerical.h"


namespace cppargparse {


template <>
/**
 * @brief The argument struct for the double type.
 */
struct argument<double>
{
    /**
     * @brief Try to parse a command line argument as a double.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The double value of the command line argument next in line.
     */
    static double parse(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &)
    {
        return numerical_argument::parse<double>(
            cmdarg,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stod),
            "double"
        );
    }


    /**
     * @brief Try to convert a command line argument to a double value.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The double value of the command line argument.
     */
    static double convert(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &)
    {
        return numerical_argument::convert<double>(
            cmdarg,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stod),
            "double"
        );
    }
};


template <>
/**
 * @brief The type_trait struct for the long double type.
 */
struct argument<long double>
{
    /**
     * @brief Try to parse a command line argument as a long double.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The long double value of the command line argument next in line.
     */
    static long double parse(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &)
    {
        return numerical_argument::parse<long double>(
            cmdarg,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stold),
            "long double"
        );
    }

    /**
     * @brief Try to convert a command line argument to a long double value.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The long double value of the command line argument.
     */
    static long double convert(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &)
    {
        return numerical_argument::convert<long double>(
            cmdarg,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stold),
            "long double"
        );
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_DOUBLE_H
