#ifndef CPPARGPARSE_TYPES_TYPE_TRAITS_INT_H
#define CPPARGPARSE_TYPES_TYPE_TRAITS_INT_H

#include <algorithm>
#include <stdexcept>

#include <cppargparse/globals.h>
#include "type_traits_stub.h"


namespace cppargparse::types {


template <>
/**
 * @brief The type_trait struct for the integer type.
 */
struct type_trait<int>
{
    /**
     * @brief Looks for a given key inside an argument list container and, if found, returns its integer value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value An integer pointer to store the value at.
     * @param default_value The default value for the argument key.
     *
     * @return The integer value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, int * const value, const int &default_value)
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
     * @brief Looks for a given key inside an argument list container and, if found, returns its integer value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value An integer pointer to store the value at.
     *
     * @return The integer value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, int * const value)
    {
        // Look for <key> inside <args>.
        auto key_it = std::find(g_args.begin(), g_args.end(), key);

        if (key_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Advance the iterator once to get the key's integer value.
        auto value_it = std::next(key_it);

        if (value_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Store the found value at the integer pointer location.
        try
        {
            *value = std::stoi(*value_it);
            return true;
        }
        catch (std::invalid_argument const &)
        {
            return false;
        }
        catch (std::out_of_range const &)
        {
            return false;
        }
    }
};


} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPES_TYPE_TRAITS_INT_H
