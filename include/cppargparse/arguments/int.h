#ifndef CPPARGPARSE_ARGUMENTS_INT_H
#define CPPARGPARSE_ARGUMENTS_INT_H

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
#include "numerical.h"


namespace cppargparse {


template <typename T>
/**
 * @brief Custom std::stou() implementation for use without default parameters.
 *
 * @tparam T The unsigned integer type to cast the result to.
 * @param s The string to convert to the typed T value.
 *
 * @return The T value of the string passed.
 */
static T wrap_stou(const std::string &s)
{
    unsigned long long result = std::stoull(s);

    if (result > std::numeric_limits<unsigned int>::max())
    {
        throw std::out_of_range("stou");
    }

    return static_cast<T>(result);
}


template <typename T>
/**
 * @brief std::stoi() wrapper for use without default parameters.
 *
 * @tparam T The signed integer type to cast the result to.
 * @param s The string to convert to the typed T value.
 *
 * @return The T value of the string passed.
 */
static T wrap_stoi(const std::string &s)
{
    return static_cast<T>(std::stoi(s));
}


template <typename T>
/**
 * @brief std::stoul() wrapper for use without default parameters.
 *
 * @tparam T The unsigned integer type to cast the result to.
 * @param s The string to convert to the typed T value.
 *
 * @return The T value of the string passed.
 */
static T wrap_stoul(const std::string &s)
{
    return static_cast<T>(std::stoul(s));
}


template <typename T>
/**
 * @brief std::stol() wrapper for use without default parameters.
 *
 * @tparam T The signed integer type to cast the result to.
 * @param s The string to convert to the typed T value.
 *
 * @return The T value of the string passed.
 */
static T wrap_stol(const std::string &s)
{
    return static_cast<T>(std::stol(s));
}


template <typename T>
/**
 * @brief Char wrapper for use without default parameters.
 *
 * @tparam T The char type to cast the result to.
 * @param s The string to convert to the typed T value.
 *
 * @return The T value of the string passed.
 */
static T wrap_char(const std::string &s)
{
    if (s.size() == 0)
    {
        throw std::out_of_range("char");
    }

    if (s.at(0) == '-')
    {
        if (s.size() < 2)
        {
            throw std::out_of_range("char");
        }

        return static_cast<T>(s.at(1));
    }

    return static_cast<T>(s.at(0));
}


#define CPPARGPARSE_INT_ARGUMENT(type, wrapper) \
template <> \
struct argument<type> \
{ \
    CPPARGPARSE_PARSE_ARGUMENT(type) \
\
    CPPARGPARSE_NUMERICAL_CONVERT(type, wrapper<type>) \
}


/* <cstdint> type implementations. */

CPPARGPARSE_INT_ARGUMENT(uint8_t, wrap_char);
CPPARGPARSE_INT_ARGUMENT(int8_t, wrap_char);
CPPARGPARSE_INT_ARGUMENT(char, wrap_char);

CPPARGPARSE_INT_ARGUMENT(uint16_t, wrap_stou);
CPPARGPARSE_INT_ARGUMENT(int16_t, wrap_stoi);
CPPARGPARSE_INT_ARGUMENT(uint32_t, wrap_stou);
CPPARGPARSE_INT_ARGUMENT(int32_t, wrap_stoi);
CPPARGPARSE_INT_ARGUMENT(uint64_t, wrap_stoul);
CPPARGPARSE_INT_ARGUMENT(int64_t, wrap_stol);


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_INT_H
