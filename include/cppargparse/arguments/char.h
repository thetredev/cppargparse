#ifndef CPPARGPARSE_ARGUMENTS_CHAR_H
#define CPPARGPARSE_ARGUMENTS_CHAR_H

#include <algorithm>
#include <sstream>
#include <string>

#include <cppargparse/cmd.h>
#include <cppargparse/errors.h>

#include "argument.h"


namespace cppargparse {


template <>
/**
 * @brief The argument struct for the char type.
 */
struct argument<char>
{
    /**
     * @brief Try to parse a command line argument as a char.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The char value of the command line argument next in line.
     */
    static char parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &cmdargs)
    {
        return convert(cmd, std::next(position), cmdargs);
    }


    /**
     * @brief Try to convert a command line argument to a char value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The char value of the command line argument.
     */
    static char convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        if (position == cmd.cend())
        {
            throw errors::CommandLineOptionError(error_message(std::prev(position), "char"));
        }

        try
        {
            return (*position)[0];
        }

        catch (const std::invalid_argument &)
        {
            throw errors::CommandLineOptionError(error_message(position, "char"));
        }
        catch (const std::out_of_range &)
        {
            throw errors::CommandLineOptionError(error_message(position, "char"));
        }
    }


    /**
     * @brief Generate an error message for a value that's not a char.
     *
     * @param position The command line argument iterator.
     *
     * @return An error message for a value that's not a char.
     */
    static const char *error_message(const cmd::CommandLinePosition_t &position, const char *data_type)
    {
        std::ostringstream message;
        message << "Couldn't convert " << *position << "to type <" << data_type << ">";

        return message.str().c_str();
    }
};


template <>
/**
 * @brief The argument struct for the unsigned char type.
 */
struct argument<unsigned char>
{
    /**
     * @brief Try to parse a command line argument as an unsigned char.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     *
     * @return The unsigned char value of the command line argument next in line.
     */
    static unsigned char parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &cmdargs)
    {
        return convert(cmd, std::next(position), cmdargs);
    }


    /**
     * @brief Try to convert a command line argument to an unsigned char value.
     *
     * @param cmd The command line.
     * @param position position The command line argument iterator.
     *
     * @return The unsigned char value of the command line argument.
     */
    static unsigned char convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &)
    {
        if (position == cmd.cend())
        {
            throw errors::CommandLineOptionError(error_message(std::prev(position), "unsigned char"));
        }

        try
        {
            const std::string value {*position};
            return static_cast<unsigned char>(value.at(0));
        }

        catch (const std::invalid_argument &)
        {
            throw errors::CommandLineOptionError(error_message(position, "unsigned char"));
        }
        catch (const std::out_of_range &)
        {
            throw errors::CommandLineOptionError(error_message(position, "unsigned char"));
        }
    }


    /**
     * @brief Generate an error message for a value that's not a char.
     *
     * @param position The command line argument iterator.
     *
     * @return An error message for a value that's not a char.
     */
    static const char *error_message(const cmd::CommandLinePosition_t &position, const char *data_type)
    {
        std::ostringstream message;
        message << "Couldn't convert " << *position << "to type <" << data_type << ">";

        return message.str().c_str();
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_CHAR_H
