#ifndef CPPARGPARSE_TYPE_TRAITS_VECTOR_H
#define CPPARGPARSE_TYPE_TRAITS_VECTOR_H

#include <algorithm>
#include <sstream>
#include <vector>

#include <cppargparse/algorithm.h>
#include <cppargparse/errors.h>
#include <cppargparse/globals.h>

#include "default.h"


namespace cppargparse::types {


template <typename T>
/**
 * @brief The type_trait struct for the integer type.
 */
struct type_trait<std::vector<T>>
{
    /**
     * @brief Try to parse and return the integer value for an argument. Throw a #parser::ParserException on failure.
     *
     * @param key_it The argument key iterator.
     *
     * @return The parsed integer value for an argument on success or throw a #parser::ParserException on failure.
     */
    static const std::vector<T> parse(const ArgumentList_t::const_iterator &key_it)
    {
        auto value_strings = algorithm::collect_arg_values(key_it);
        std::vector<T> values;

        for (auto value_string_it : value_strings)
        {
            values.emplace_back(type_trait<T>::convert(value_string_it));
        }

        return values;
    }

    /**
     * @brief Generate an error message for a value that's not an integer.
     *
     * @param value_it The argument value iterator.
     *
     * @return An error message for a value that's not an integer.
     */
    static const char *error_message(const ArgumentList_t::const_iterator &value_it)
    {
        std::ostringstream message;
        message << "Couldn't parse '" << *value_it << "' as an integer.";

        return message.str().c_str();
    }
};


} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPE_TRAITS_VECTOR_H
