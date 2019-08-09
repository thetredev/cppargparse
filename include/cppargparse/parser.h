#ifndef CPPARGPARSE_PARSER_H
#define CPPARGPARSE_PARSER_H

#include <sstream>

#include <cppargparse/algorithm.h>
#include <cppargparse/arguments.h>
#include <cppargparse/globals.h>

#include "errors.h"


namespace cppargparse::parser {


/**
 * @brief Look for a flag within the global command line argument list.
 *
 * @param arg The argument string to look for.
 *
 * @return Whether the flag is present in the global command line argument.
 */
inline static bool parse_flag(const std::string &flag)
{
    try
    {
        (void)algorithm::find_cmdarg(flag);
        return true;
    }

    catch (const errors::CommandLineArgumentError &)
    {
        return false;
    }
}


template <typename T>
/**
 * @brief Try to parse and return an argument value of any type. Throw a #parser::ParserException on failure.
 *
 * This method uses a pre-defined built in and custom argument types.
 *
 * @param arg The argument string to look for..
 *
 * @return The parsed argument value of any type or throw a #parser::ParserException on failure.
 */
inline static const T parse_arg(const std::string &arg)
{
    try
    {
        auto cmdarg = algorithm::find_cmdarg(arg);
        g_options.emplace_back(cmdarg);

        return argument<T>::parse(cmdarg);
    }

    catch (const errors::CommandLineArgumentError &ex)
    {
        throw errors::CommandLineArgumentError(ex);
    }
    catch (const errors::CommandLineOptionError &ex)
    {
        throw errors::CommandLineOptionError(ex);
    }
}


template <typename T>
/**
 * @brief Parse and return an argument value of any type. Return the default value on failure.
 *
 * This method uses a pre-defined built in and custom argument types.
 *
 * @param arg The argument string to look for.
 * @param default_value The default value if the argument string couldn't be parsed.
 *
 * @return The parsed argument value of any type or the default value if the argument string couldn't be parsed.
 */
inline static const T parse_arg(const std::string &arg, const T &default_value)
{
    try
    {
        auto cmdarg = algorithm::find_cmdarg(arg);
        g_options.emplace_back(cmdarg);

        return argument<T>::parse(cmdarg);
    }

    catch (const errors::CommandLineArgumentError &)
    {
        return default_value;
    }
    catch (const errors::CommandLineOptionError &)
    {
        return default_value;
    }
}


} // namespace cppargparse::parser

#endif // CPPARGPARSE_PARSER_H
