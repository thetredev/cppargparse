#ifndef CPPARGPARSE_ARGUMENTS_NUMERICAL_H
#define CPPARGPARSE_ARGUMENTS_NUMERICAL_H

#include <algorithm>
#include <functional>
#include <sstream>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"


// https://stackoverflow.com/questions/46587694/passing-function-with-defaults-as-argument-ignoring-them/46588390
#define CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_RETURNS(...) \
  noexcept(noexcept(__VA_ARGS__)) \
  -> decltype( __VA_ARGS__ ) \
  { return __VA_ARGS__; }


#define CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(...) \
  [](auto&&...args) \
  CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_RETURNS( __VA_ARGS__( decltype(args)(args)... ))



namespace cppargparse::numerical_argument {


/**
 * @brief Generate an error message for a value that's not a numerical value.
 *
 * @param cmdarg The command line argument iterator.
 *
 * @return An error message for a value that's not a numerical value.
 */
static const std::string error_message(const types::CommandLineArgument_t &cmdarg, const std::string &type_string)
{
    std::ostringstream message;
    message << "Couldn't convert '" << *cmdarg << "' to type <" << type_string << ">.";
    std::string x = message.str();

    return message.str();
}


/**
 * @brief Try to convert a command line argument to a numerical value. Throw a #parser::ParserException on failure.
 *
 * @param cmdarg The command line argument iterator.
 *
 * @return The numerical value of the command line argument on success or throw a #parser::ParserException on failure.
 */
template <typename T>
static T convert(
        const types::CommandLineArgument_t &cmdarg,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string
    )
{
    try
    {
        return numerical_converter(*cmdarg, 0);
    }

    catch (std::invalid_argument const &)
    {
        throw errors::CommandLineOptionError(error_message(cmdarg, type_string));
    }
    catch (std::out_of_range const &)
    {
        throw errors::CommandLineOptionError(error_message(cmdarg, type_string));
    }
}


/**
 * @brief Try to parse a command line argument as a numerical value. Throw a #parser::ParserException on failure.
 *
 * @param cmdarg The command line argument iterator.
 *
 * @return The numerical value of the command line argument next in line on success or throw a #parser::ParserException on failure.
 */
template <typename T>
static T parse(const types::CommandLineArgument_t &cmdarg,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string)
{
    return convert(std::next(cmdarg), numerical_converter, type_string);
}


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_NUMERICAL_H
