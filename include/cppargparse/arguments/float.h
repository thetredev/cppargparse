#ifndef CPPARGPARSE_ARGUMENTS_FLOAT_H
#define CPPARGPARSE_ARGUMENTS_FLOAT_H

#include <algorithm>

#include <cppargparse/types.h>

#include "default.h"
#include "numerical.h"


namespace cppargparse {


template <>
/**
 * @brief The argument struct for the float type.
 */
struct argument<float>
{
    /**
     * @brief Try to parse a command line argument as a float.
     *
     * @param position The command line argument iterator.
     *
     * @return The float value of the command line argument next in line.
     */
    static float parse(
            const types::CommandLine_t &,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument::parse<float>(
            position,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stof),
            "float"
        );
    }

    /**
     * @brief Try to convert a command line argument to a float value..
     *
     * @param position The command line argument iterator.
     *
     * @return The float value of the command line argument.
     */
    static float convert(
            const types::CommandLine_t &,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument::convert<float>(
            position,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stof),
            "float"
        );
    }
};

} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_FLOAT_H
