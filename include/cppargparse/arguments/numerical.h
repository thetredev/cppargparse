#ifndef CPPARGPARSE_ARGUMENTS_NUMERICAL_H
#define CPPARGPARSE_ARGUMENTS_NUMERICAL_H

#include <algorithm>
#include <functional>
#include <sstream>

#include <cppargparse/errors.h>
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
 * @param type_string The numerical type's string representation.
 *
 * @return An error message for a value that's not a numerical value.
 */
static const std::string error_message(const types::CommandLinePosition_t &position, const std::string &type_string)
{
    std::ostringstream message;
    message << "Couldn't convert '" << *position << "' to type <" << type_string << ">.";
    std::string x = message.str();

    return message.str();
}


/**
 * @brief Try to convert a command line argument value to a numerical value.
 *
 * @param cmdarg The command line argument iterator.
 * @param numerical_converter The function used to convert the cmdarg into a numerical value.
 * @param type_string The numerical type's string representation.
 *
 * @return The numerical value of the command line argument.
 * @throws #cppargparse::errors::CommandLineOptionError if the conversion was unsuccessful.
 */
template <typename T>
static T convert(
        const types::CommandLinePosition_t &position,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string
    )
{
    try
    {
        return numerical_converter(*position, 0);
    }

    catch (std::invalid_argument const &)
    {
        throw errors::CommandLineOptionError(error_message(position, type_string));
    }
    catch (std::out_of_range const &)
    {
        throw errors::CommandLineOptionError(error_message(position, type_string));
    }
}


/**
 * @brief Try to parse a command line argument as a numerical value.
 *
 * @param cmdarg The command line argument iterator.
 * @param numerical_converter The function used to convert the cmdarg into a numerical value.
 * @param type_string The numerical type's string representation.
 *
 * @return The numerical value of the command line argument next in line.
 */
template <typename T>
static T parse(const types::CommandLinePosition_t &position,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string)
{
    return convert(std::next(position), numerical_converter, type_string);
}


} // namespace cppargparse::numerical_argument

#endif // CPPARGPARSE_ARGUMENTS_NUMERICAL_H
