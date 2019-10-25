#ifndef CPPARGPARSE_ARGUMENT_INT_H
#define CPPARGPARSE_ARGUMENT_INT_H

#include <algorithm>
#include <limits>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
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
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
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
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
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


template <>
/**
 * @brief The argument struct for the unsigned int type.
 */
struct argument<unsigned int>
{
    /**
     * @brief Try to parse a command line argument as an unsigned int.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The unsigned int value of the command line argument next in line.
     */
    static unsigned int parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<unsigned int>::convert(cmd, std::next(position), &stou, "unsigned int");
    }


    /**
     * @brief Try to convert a command line argument to anunsigned int value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The unsigned int value of the command line argument.
     */
    static unsigned int convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<unsigned int>::convert(cmd, position, &stou, "unsigned int");
    }


    /**
     * @brief Convert a string to an unsigned long and return its unsigned int value.
     *
     * @param s The string to convert to an unsigned int.
     *
     * @return The unsigned int value of the string passed.
     * @throw std::out_of_range if the converted string value is outside of the range of the unsigned int type.
     */
    static unsigned int stou(const std::string &s)
    {
        unsigned long result = std::stoul(s);

        if (result > std::numeric_limits<unsigned int>::max())
        {
            throw std::out_of_range("stou");
        }

        return static_cast<unsigned int>(result);
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENT_INT_H
