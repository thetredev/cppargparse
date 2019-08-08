#ifndef CPPARGPARSE_TYPE_TRAITS_FLOAT_H
#define CPPARGPARSE_TYPE_TRAITS_FLOAT_H

#include <algorithm>
#include <sstream>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>

#include "default.h"


namespace cppargparse::types {


template <>
/**
 * @brief The type_trait struct for the float type.
 */
struct type_trait<float>
{
    /**
     * @brief Try to parse and return the float value for an argument. Throw a #parser::ParserException on failure.
     *
     * @param key_it The argument key iterator.
     *
     * @return The parsed float value for an argument on success or throw a #parser::ParserException on failure.
     */
    static float parse(const ArgumentList_t::const_iterator &key_it)
    {
        return convert(std::next(key_it));
    }

    /**
     * @brief Try to convert and return the given argument value as a float. Throw a #parser::ParserException on failure.
     *
     * @param value_it The argument value iterator.
     *
     * @return The converted float value of an argument value on success or throw a #parser::ParserException on failure.
     */
    static float convert(const ArgumentList_t::const_iterator &value_it)
    {
        try
        {
            return std::stof(*value_it);
        }

        catch (std::invalid_argument const &)
        {
            throw errors::ParserError(error_message(value_it));
        }
        catch (std::out_of_range const &)
        {
            throw errors::ParserError(error_message(value_it));
        }
    }

    /**
     * @brief Generate an error message for a value that's not a float.
     *
     * @param value_it The argument value iterator.
     *
     * @return An error message for a value that's not a float.
     */
    static const char *error_message(const ArgumentList_t::const_iterator &value_it)
    {
        std::ostringstream message;
        message << "Couldn't parse '" << *value_it << "' as a float value.";

        return message.str().c_str();
    }
};

} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPE_TRAITS_FLOAT_H
