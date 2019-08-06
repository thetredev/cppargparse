#ifndef CPPARGPARSE_TYPE_TRAITS_STRING_H
#define CPPARGPARSE_TYPE_TRAITS_STRING_H

#include <algorithm>
#include <string>

#include <cppargparse/globals.h>
#include "stub.h"


namespace cppargparse::types {


template <>
/**
 * @brief The type_trait struct for the std::string type.
 */
struct type_trait<std::string>
{
    /**
     * @brief Looks for a given key inside an argument list container and, if found, returns its std::string value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value A std::string pointer to store the value at.
     * @param default_value The default value for the argument key.
     *
     * @return The std::string value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, std::string * const value, const std::string &default_value)
    {
        // Look for <key> inside <args>.
        auto key_it = std::find(g_args.begin(), g_args.end(), key);

        if (key_it == g_args.end())
        {
            // Store the default std::string value at the std::string pointer location, if it can't be found.
            *value = default_value;

            // Return false to signal failure.
            return false;
        }

        // Call parse() without the default value to get the std::string value for <key>.
        return parse(key, value);
    }

    /**
     * @brief Looks for a given key inside an argument list container and, if found, returns its std::string value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value A std::string pointer to store the value at.
     *
     * @return The std::string value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, std::string * const value)
    {
        // Look for <key> inside <args>.
        auto key_it = std::find(g_args.begin(), g_args.end(), key);

        if (key_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Advance the iterator once to get the key's string value.
        auto value_it = std::next(key_it);

        if (value_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Store the found value at the std::string pointer location.
        *value = *value_it;

        // Return true to signal success.
        return true;
    }
};


#endif // CPPARGPARSE_TYPE_TRAITS_STRING_H

} // namespace cppargparse::types
