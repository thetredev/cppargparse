#ifndef CPPARGPARSE_ARGUMENT_LONG_H
#define CPPARGPARSE_ARGUMENT_LONG_H

#include <algorithm>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
#include "numerical.h"


namespace cppargparse {


template <>
/**
 * @brief The argument struct for the long type.
 */
struct argument<long>
{
    /**
     * @brief Try to parse a command line argument as a long.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The long value of the command line argument next in line.
     */
    static long parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<long>::convert(cmd, std::next(position), &wrap, "long");
    }

    /**
     * @brief Try to convert a command line argument to a long value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The long value of the command line argument.
     */
    static long convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<long>::convert(cmd, position, &wrap, "long");
    }

    /**
     * @brief Wrap std::stol() for use without default parameters.
     *
     * @param s The string to convert to a long.
     *
     * @return The long value of the string passed.
     */
    static long wrap(const std::string &s)
    {
        return std::stol(s);
    }
};


template <>
/**
 * @brief The type_trait struct for the long long type.
 */
struct argument<long long>
{
    /**
     * @brief Try to parse a command line argument as a long long.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The long long value of the command line argument next in line.
     */
    static long long parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<long long>::convert(cmd, std::next(position), &wrap, "long long");
    }

    /**
     * @brief Try to convert a command line argument to a long long value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The long double long of the command line argument.
     */
    static long double convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<long long>::convert(cmd, position, &wrap, "long long");
    }

    /**
     * @brief Wrap std::stoll() for use without default parameters.
     *
     * @param s The string to convert to a long long.
     *
     * @return The long long value of the string passed.
     */
    static long long wrap(const std::string &s)
    {
        return std::stoll(s);
    }
};


template <>
/**
 * @brief The argument struct for the unsigned long type.
 */
struct argument<unsigned long>
{
    /**
     * @brief Try to parse a command line argument as an unsigned long.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The unsigned long value of the command line argument next in line.
     */
    static unsigned long parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<unsigned long>::convert(cmd, std::next(position), &wrap, "unsigned long");
    }

    /**
     * @brief Try to convert a command line argument to an unsigned long value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The unsigned long value of the command line argument.
     */
    static unsigned long convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<unsigned long>::convert(cmd, position, &wrap, "unsigned long");
    }

    /**
     * @brief Wrap std::stoul() for use without default parameters.
     *
     * @param s The string to convert to an unsigned long.
     *
     * @return The unsigned long value of the string passed.
     */
    static unsigned long wrap(const std::string &s)
    {
        return std::stoul(s);
    }
};


template <>
/**
 * @brief The argument struct for the unsigned long long type.
 */
struct argument<unsigned long long>
{
    /**
     * @brief Try to parse a command line argument as an unsigned long long.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The unsigned long long value of the command line argument next in line.
     */
    static unsigned long long parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<unsigned long long>::convert(cmd, std::next(position), &wrap, "unsigned long long");
    }

    /**
     * @brief Try to convert a command line argument to an unsigned long long value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The unsigned long long value of the command line argument.
     */
    static unsigned long long convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        return numerical_argument<unsigned long long>::convert(cmd, position, &wrap, "unsigned long long");
    }

    /**
     * @brief Wrap std::stoull() for use without default parameters.
     *
     * @param s The string to convert to an unsigned long long.
     *
     * @return The unsigned long long value of the string passed.
     */
    static unsigned long long wrap(const std::string &s)
    {
        return std::stoull(s);
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENT_LONG_H
