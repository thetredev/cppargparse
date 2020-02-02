#ifndef CPPARGPARSE_ARGUMENTS_DOUBLE_H
#define CPPARGPARSE_ARGUMENTS_DOUBLE_H

#include <algorithm>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
#include "numerical.h"


namespace cppargparse {


/**
 * @brief Wrap std::stod() for use without default parameters.
 *
 * @param s The string to convert to the typed double value.
 *
 * @return The double value of the string passed.
 */
static double wrap_stod(const std::string &s)
{
    return std::stod(s);
}

CPPARGPARSE_NUMERICAL_ARGUMENT(double, wrap_stod);


/**
 * @brief Wrap std::stold() for use without default parameters.
 *
 * @param s The string to convert to the typed long double value.
 *
 * @return The long double value of the string passed.
 */
static long double wrap_stold(const std::string &s)
{
    return std::stold(s);
}

CPPARGPARSE_NUMERICAL_ARGUMENT(long double, wrap_stold);


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_DOUBLE_H
