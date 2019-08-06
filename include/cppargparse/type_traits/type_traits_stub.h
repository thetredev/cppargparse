#ifndef CPPARGPARSE_TYPE_TRAITS_STUB_H
#define CPPARGPARSE_TYPE_TRAITS_STUB_H

#include <cppargparse/types.h>


namespace cppargparse::types {


template <typename T>
/**
 * @brief The default type_trait struct. Provides stub methods returning stub values.
 */
struct type_trait
{
    /**
     * @brief Default type_trait stub for a given default value.
     *
     * @param key The key to look for.
     * @param value A pointer to store the value at.
     * @param default_value The default value.
     *
     * @return false
     */
    static bool parse(const Key_t &key, T * const value, const T &default_value)
    {
        // STUB
        return false;
    }

    /**
     * @brief Default type_trait stub.
     *
     * @param key The key to look for.
     * @param value A pointer to store the value at.
     *
     * @return false
     */
    static bool parse(const Key_t &key, T * const value)
    {
        // STUB
        return false;
    }
};


} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPE_TRAITS_STUB_H
