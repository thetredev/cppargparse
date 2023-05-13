#ifndef CPPARGPARSE_ARGUMENTS_ARGUMENT_H
#define CPPARGPARSE_ARGUMENTS_ARGUMENT_H

#include <functional>
#include <sstream>

#include <cppargparse/cmd.h>
#include <cppargparse/errors.h>


namespace cppargparse {


#define CPPARGPARSE_PARSE_ARGUMENT(type) \
    static type parse( \
        const cmd::CommandLine_t &cmd, \
        const cmd::CommandLinePosition_t &position, \
        const cmd::CommandLineArguments_t &cmdargs) \
    { \
        return common::parse_argument<type>(cmd, position, cmdargs, convert); \
    }


namespace common {


template <typename T>
/**
 * @brief Stub error message.
 *
 * @param position The command line position.
 * @return An empty C-style string.
 */
static const char *error_message(const cmd::CommandLinePosition_t &position)
{
    std::ostringstream message;
    message << "Couldn't convert " << *position << "to type <" << typeid(T).name() << ">";

    return message.str().c_str();
}


template <typename T>
/**
 * @brief Parse a command line argument and return its converted value.
 *
 * @param cmd The command line.
 * @param position The command line position of the argument.
 * @param cmdargs The command line arguments.
 * @param converter The argument converter function.
 *
 * @return The converted command line argument value.
 */
T parse_argument(const cmd::CommandLine_t &cmd, const cmd::CommandLinePosition_t &position, const cmd::CommandLineArguments_t &cmdargs,
                 const std::function<T(const cmd::CommandLine_t &, const cmd::CommandLinePosition_t &, const cmd::CommandLineArguments_t &)> &converter)
{
    return converter(cmd, std::next(position), cmdargs);
}

} // namespace common


template <typename T>
/**
 * @brief The default argument struct. Provides stub methods returning stub values.
 *
 * @tparam T The argument type. Must be non-abstract and have a default constructor.
 */
struct argument
{
    /**
     * @brief Stub parse method for any type.
     *
     * @return A new instance of the template type.
     */
    static const T parse(
            const cmd::CommandLine_t &,
            const cmd::CommandLinePosition_t &,
            const cmd::CommandLineArguments_t &)
    {
        return T();
    }


    /**
     * @brief Stub convert method for any type.
     *
     * @return A new instance of the template type.
     */
    static const T convert(
            const cmd::CommandLine_t &,
            const cmd::CommandLinePosition_t &,
            const cmd::CommandLineArguments_t &)
    {
        return T();
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_ARGUMENT_H
