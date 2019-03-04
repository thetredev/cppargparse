#ifndef CPPARGPARSE_PARSER_PARSER_H
#define CPPARGPARSE_PARSER_PARSER_H

#include <types.h>
#include <type_traits/type_traits.h>


namespace cppargparse::parser {


/**
 * @brief Converts the C-style command line arguments into an argument list container.
 *
 * @param argc The length of the argv array.
 * @param argv The command line argument array passed by the OS.
 *
 * @return The argv array as an argument list container.
 */
void parse_arg_list(int argc, char *argv[])
{
    types::ArgumentList_t temp(argv, argv + argc);

    g_args.assign(temp.cbegin(), temp.cend());
}


template <typename T>
/**
 * @brief Lookup #g_args for the argument key and return its typed value.
 *
 * @param key The argument key to look for.
 *
 * @return The typed value for the argument key.
 */
inline static const T parse_arg(types::Key_t key)
{
    T value;

    if (!types::type_trait<T>::parse(key, &value))
    {
        /// todo: error handling
    }

    return value;
}


template <typename T>
/**
 * @brief Lookup #g_args for the argument key and return its typed value. Return a given default value in case of failure.
 *
 * @param key The argument key to look for.
 * @param default_value The default typed value for the argument key.
 *
 * @return The typed value for the argument key.
 */
inline static const T parse_arg(types::Key_t key, T default_value)
{
    T value;

    if (!types::type_trait<T>::parse(key, &value, default_value))
    {
        /// todo: error handling
    }

    return value;
}


} // namespace cppargparse::parse

#endif // CPPARGPARSE_PARSER_PARSER_H
