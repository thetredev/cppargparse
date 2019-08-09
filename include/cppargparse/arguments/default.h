#ifndef CPPARGPARSE_ARGUMENTS_DEFAULT_H
#define CPPARGPARSE_ARGUMENTS_DEFAULT_H

#include <cppargparse/types.h>


namespace cppargparse {


template <typename T>
/**
 * @brief The default type_trait struct. Provides stub methods returning stub values.
 */
struct argument
{
    /**
     * @brief Stub parse method for any type.
     *
     * @param key_it The argument key iterator.
     *
     * @return A new instance of the template type.
     */
    static const T parse(const types::ArgumentList_t::const_iterator &key_it)
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
    static const T convert(const types::ArgumentList_t::const_iterator &value_it)
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
    static const char *error_message(const types::ArgumentList_t::const_iterator &value_it)
    {
        return "";
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_DEFAULT_H
