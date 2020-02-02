#ifndef CPPARGPARSE_ARGUMENTS_FLOAT_H
#define CPPARGPARSE_ARGUMENTS_FLOAT_H

#include <algorithm>
#include <string>

#include <cppargparse/cmd.h>

#include "argument.h"
#include "numerical.h"


namespace cppargparse {


/**
 * @brief Wrap std::stof() for use without default parameters.
 *
 * @param s The string to convert to the typed float value.
 *
 * @return The float value of the string passed.
 */
static float wrap_stof(const std::string &s)
{
    return std::stof(s);
}

CPPARGPARSE_NUMERICAL_ARGUMENT(float, wrap_stof);


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_FLOAT_H
