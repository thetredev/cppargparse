#ifndef CPPARGPARSE_ARGUMENTS_LONG_H
#define CPPARGPARSE_ARGUMENTS_LONG_H

#include <algorithm>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
#include "numerical.h"


namespace cppargparse {


/**
 * @brief Wrap std::stoll() for use without default parameters.
 *
 * @param s The string to convert to the typed long long value.
 *
 * @return The long long value of the string passed.
 */
static long long wrap_stoll(const std::string &s)
{
    return std::stoll(s);
}

CPPARGPARSE_NUMERICAL_ARGUMENT(long long, wrap_stoll);


/**
 * @brief Wrap std::stoull() for use without default parameters.
 *
 * @param s The string to convert to the typed unsigned long long value.
 *
 * @return The unsigned long long value of the string passed.
 */
static unsigned long long wrap_stoull(const std::string &s)
{
    return std::stoull(s);
}

CPPARGPARSE_NUMERICAL_ARGUMENT(unsigned long long, wrap_stoull);


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_LONG_H
