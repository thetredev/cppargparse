#ifndef CPPARGPARSE_PARSER_PARSER_H
#define CPPARGPARSE_PARSER_PARSER_H

#include <sstream>

#include <cppargparse/algorithm.h>
#include <cppargparse/globals.h>
#include <cppargparse/type_traits/type_traits.h>

#include "errors.h"


namespace cppargparse::parser {


/**
 * @brief Parse the argument list container for a flag.
 *
 * @param key The argument key to look for.
 *
 * @return Whether the argument key is present in the argument list container.
 */
inline static bool parse_flag(const types::Key_t &key)
{
    try
    {
        (void)algorithm::find_key(key);
        return true;
    }

    catch (const errors::ArgumentKeyError &)
    {
        return false;
    }
}


template <typename T>
/**
 * @brief Try to parse and return an argument value of any type. Throw a #parser::ParserException on failure.
 *
 * This method uses a pre-defined type trait, built-in or custom.
 *
 * @param key The argument key to look for in #g_args.
 *
 * @return The parsed argument value of any type or throw a #parser::ParserException on failure.
 */
inline static const T parse_arg(const types::Key_t &key)
{
    try
    {
        auto key_it = algorithm::find_key(key);
        g_keys.emplace_back(key_it);

        return types::type_trait<T>::parse(key_it);
    }
    catch (const errors::ParserError &ex)
    {
        throw errors::ParserError(ex);
    }
}


template <typename T>
/**
 * @brief Parse and return an argument value of any type. Return the default value on failure.
 *
 * This method uses a pre-defined type trait, built-in or custom.
 *
 * @param key The argument key to look for in #g_args.
 *
 * @return The parsed argument value of any type or the default value on failure.
 */
inline static const T parse_arg(const types::Key_t &key, const T &default_value)
{
    try
    {
        auto key_it = algorithm::find_key(key);
        g_keys.emplace_back(key_it);

        return types::type_trait<T>::parse(key_it);
    }
    catch (const errors::ParserError &)
    {
        return default_value;
    }
    catch (const errors::ArgumentKeyError &)
    {
        return default_value;
    }
}


} // namespace cppargparse::parser

#endif // CPPARGPARSE_PARSER_PARSER_H
