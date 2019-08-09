#ifndef CPPARGPARSE_ARGUMENTS_FLOAT_H
#define CPPARGPARSE_ARGUMENTS_FLOAT_H

#include <algorithm>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"
#include "numerical.h"


namespace cppargparse {


template <>
/**
 * @brief The argument struct for the float type.
 */
struct argument<float>
{
    /**
     * @brief Try to parse a command line argument as a float. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The float value of the command line argument next in line on success or throw a #parser::ParserException on failure.
     */
    static float parse(const types::CommandLineArgument_t &cmdarg)
    {
        return numerical_argument::parse<float>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stof), "float");
    }

    /**
     * @brief Try to convert a command line argument to a float value. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The float value of the command line argument on success or throw a #parser::ParserException on failure.
     */
    static float convert(const types::CommandLineArgument_t &cmdarg)
    {
        return numerical_argument::convert<float>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stof), "float");
    }
};

} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_FLOAT_H
