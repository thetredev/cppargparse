#ifndef CPPARGPARSE_TYPE_TRAITS_DEFAULT_H
#define CPPARGPARSE_TYPE_TRAITS_DEFAULT_H

#include <cppargparse/types.h>


namespace cppargparse::types {


template <typename T>
/**
 * @brief The default type_trait struct. Provides stub methods returning stub values.
 */
struct type_trait
{
    /**
     * @brief Stub parse method for any type.
     *
     * @param key_it The argument key iterator.
     *
     * @return A new instance of the template type.
     */
    static const T parse(const ArgumentList_t::const_iterator &key_it)
    {
        return T();
    }


    /**
     * @brief Stub convert method for any type.
     *
     * @param value_it The argument value iterator.
     *
     * @return A new instance of the template type.
     */
    static const T convert(const ArgumentList_t::const_iterator &value_it)
    {
        return T();
    }


    /**
     * @brief Stub error message.
     *
     * @param value_it The argument value iterator.
     *
     * @return An empty C-style string.
     */
    static const char *error_message(const ArgumentList_t::const_iterator &value_it)
    {
        return "";
    }
};


} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPE_TRAITS_DEFAULT_H
