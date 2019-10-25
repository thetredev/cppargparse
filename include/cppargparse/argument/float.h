#ifndef CPPARGPARSE_ARGUMENT_FLOAT_H
#define CPPARGPARSE_ARGUMENT_FLOAT_H

#include <algorithm>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
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
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The float value of the command line argument next in line.
     */
    static float parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<float>::convert(cmd, std::next(position), &wrap, "float");
    }

    /**
     * @brief Try to convert a command line argument to a float value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The float value of the command line argument.
     */
    static float convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<float>::convert(cmd, position, &wrap, "float");
    }

    /**
     * @brief Wrap std::stof() for use without default parameters.
     *
     * @param s The string to convert to a float.
     *
     * @return The float value of the string passed.
     */
    static float wrap(const std::string &s)
    {
        return std::stof(s);
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENT_FLOAT_H
