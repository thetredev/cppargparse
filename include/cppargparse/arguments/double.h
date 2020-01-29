#ifndef CPPARGPARSE_ARGUMENTS_DOUBLE_H
#define CPPARGPARSE_ARGUMENTS_DOUBLE_H

#include <algorithm>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
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
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The double value of the command line argument next in line.
     */
    static double parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<double>::convert(cmd, std::next(position), &wrap, "double");
    }

    /**
     * @brief Try to convert a command line argument to a double value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The double value of the command line argument.
     */
    static double convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<double>::convert(cmd, position, &wrap, "double");
    }

    /**
     * @brief Wrap std::stod() for use without default parameters.
     *
     * @param s The string to convert to a double.
     *
     * @return The double value of the string passed.
     */
    static double wrap(const std::string &s)
    {
        return std::stod(s);
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
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The long double value of the command line argument next in line.
     */
    static long double parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<long double>::convert(cmd, std::next(position), &wrap, "long double");
    }


    /**
     * @brief Try to convert a command line argument to a long double value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The long double value of the command line argument.
     */
    static long double convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<long double>::convert(cmd, position, &wrap, "long double");
    }


    /**
     * @brief Wrap std::stold() for use without default parameters.
     *
     * @param s The string to convert to a long double.
     *
     * @return The long double value of the string passed.
     */
    static long double wrap(const std::string &s)
    {
        return std::stold(s);
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_DOUBLE_H
