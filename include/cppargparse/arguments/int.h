#ifndef CPPARGPARSE_ARGUMENTS_INT_H
#define CPPARGPARSE_ARGUMENTS_INT_H

#include <algorithm>

#include <cppargparse/types.h>

#include "default.h"
#include "numerical.h"



namespace cppargparse {


template <>
/**
 * @brief The argument struct for the int type.
 */
struct argument<int>
{
    /**
     * @brief Try to parse a command line argument as an int.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The int value of the command line argument next in line.
     */
    static int parse(
            const types::CommandLine_t &,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument::parse<int>(
            position,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi),
            "int"
        );
    }

    /**
     * @brief Try to convert a command line argument to an int value.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The int value of the command line argument.
     */
    static int convert(
            const types::CommandLine_t &,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument::convert<int>(
            position,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi),
            "int"
        );
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_INT_H
