#ifndef CPPARGPARSE_TYPE_TRAITS_DOUBLE_H
#define CPPARGPARSE_TYPE_TRAITS_DOUBLE_H

#include <algorithm>
#include <stdexcept>

#include <cppargparse/globals.h>
#include "type_traits_stub.h"


namespace cppargparse::types {


template <>
/**
 * @brief The type_trait struct for the double type.
 */
struct type_trait<double>
{
    /**
     * @brief Looks for a given key inside an argument list container and, if found, returns its double value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value An double pointer to store the value at.
     * @param default_value The default value for the argument key.
     *
     * @return The double value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, double * const value, const double &default_value)
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
     * @brief Looks for a given key inside an argument list container and, if found, returns its double value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value An double pointer to store the value at.
     *
     * @return The double value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, double * const value)
    {
        // Look for <key> inside <args>.
        auto key_it = std::find(g_args.begin(), g_args.end(), key);

        if (key_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Advance the iterator once to get the key's double value.
        auto value_it = std::next(key_it);

        if (value_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Store the found value at the double pointer location.
        try
        {
            *value = std::stod(*value_it);
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


template <>
/**
 * @brief The type_trait struct for the long double type.
 */
struct type_trait<long double>
{
    /**
     * @brief Looks for a given key inside an argument list container and, if found, returns its long double value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value An long double pointer to store the value at.
     * @param default_value The default value for the argument key.
     *
     * @return The long double value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, long double * const value, const long double &default_value)
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
     * @brief Looks for a given key inside an argument list container and, if found, returns its long double value.
     *
     * @param key The key to look for inside the argument list container.
     * @param value An long double pointer to store the value at.
     *
     * @return The long double value for the given key inside an argument list container.
     */
    static bool parse(const Key_t &key, long double * const value)
    {
        // Look for <key> inside <args>.
        auto key_it = std::find(g_args.begin(), g_args.end(), key);

        if (key_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Advance the iterator once to get the key's long double value.
        auto value_it = std::next(key_it);

        if (value_it == g_args.end())
        {
            // Return false if it can't be found.
            return false;
        }


        // Store the found value at the long double pointer location.
        try
        {
            *value = std::stold(*value_it);
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

#endif // CPPARGPARSE_TYPE_TRAITS_DOUBLE_H
