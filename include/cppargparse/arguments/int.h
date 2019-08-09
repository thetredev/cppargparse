#ifndef CPPARGPARSE_ARGUMENTS_INT_H
#define CPPARGPARSE_ARGUMENTS_INT_H

#include <algorithm>

#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"
#include "numerical.h"



namespace cppargparse {


template <>
/**
 * @brief The type_trait struct for the integer type.
 */
struct argument<int>
{
    /**
     * @brief Try to parse a command line argument as an int. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The int value of the command line argument next in line on success or throw a #parser::ParserException on failure.
     */
    static int parse(const types::CommandLineArgument_t &cmdarg)
    {
        return numerical_argument::parse<int>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi), "integer");
    }

    /**
     * @brief Try to convert a command line argument to an int value. Throw a #parser::ParserException on failure.
     *
     * @param cmdarg The command line argument iterator.
     *
     * @return The int value of the command line argument on success or throw a #parser::ParserException on failure.
     */
    static int convert(const types::CommandLineArgument_t &cmdarg)
    {
        return numerical_argument::convert<int>(cmdarg, CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi), "integer");
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_INT_H
