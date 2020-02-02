#ifndef CPPARGPARSE_ARGUMENTS_NUMERICAL_H
#define CPPARGPARSE_ARGUMENTS_NUMERICAL_H

#include <functional>
#include <sstream>
#include <string>

#include <cppargparse/cmd.h>
#include <cppargparse/errors.h>

#include "argument.h"
#include "string.h"


namespace cppargparse {


template <typename T>
/**
 * @brief The conversion struct for numerical types.
 */
struct numerical_argument
{
    /**
     * @brief Try to convert a command line argument value to a numerical value.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     * @param numerical_converter The function used to convert the cmdarg into a numerical value.
     * @param type_string The numerical type's string representation.
     *
     * @return The numerical value of the command line argument.
     * @throws #cppargparse::errors::CommandLineOptionError if the conversion was unsuccessful.
     */
    static T convert(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &cmdargs,
            const std::function<T(const std::string &)> &numerical_converter)
    {
        try
        {
            const std::string string_value = argument<std::string>::convert(cmd, position, cmdargs);
            return numerical_converter(string_value);
        }

        catch (const errors::CommandLineOptionError &error)
        {
            throw error;
        }
        catch (const std::invalid_argument &)
        {
            throw errors::CommandLineOptionError(common::error_message<T>(std::prev(position)));
        }
        catch (const std::out_of_range &)
        {
            throw errors::CommandLineOptionError(common::error_message<T>(std::prev(position)));
        }
    }
};


#define CPPARGPARSE_NUMERICAL_CONVERT(type, wrapper) \
    static type convert( \
        const cmd::CommandLine_t &cmd, \
        const cmd::CommandLinePosition_t &position, \
        const cmd::CommandLineArguments_t &cmdargs) \
    { \
        return numerical_argument<type>::convert(cmd, position, cmdargs, &wrapper); \
    }


#define CPPARGPARSE_NUMERICAL_ARGUMENT(type, wrapper) \
template <> \
struct argument<type> \
{ \
    CPPARGPARSE_PARSE_ARGUMENT(type) \
\
    CPPARGPARSE_NUMERICAL_CONVERT(type, wrapper) \
}


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_NUMERICAL_H
