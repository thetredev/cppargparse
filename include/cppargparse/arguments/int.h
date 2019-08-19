#ifndef CPPARGPARSE_ARGUMENTS_INT_H
#define CPPARGPARSE_ARGUMENTS_INT_H

#include <algorithm>
#include <string>

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
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The int value of the command line argument next in line.
     */
    static int parse(
            const types::CommandLine_t &cmd,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument<int>::convert(cmd, std::next(position), &wrap, "int");
    }

    /**
     * @brief Try to convert a command line argument to an int value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The int value of the command line argument.
     */
    static int convert(
            const types::CommandLine_t &cmd,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument<int>::convert(cmd, position, &wrap, "int");
    }

    /**
     * @brief Wrap std::stoi() for use without default parameters.
     *
     * @param s The string to convert to an int.
     *
     * @return The int value of the string passed.
     */
    static int wrap(const std::string &s)
    {
        return std::stoi(s);
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_INT_H
