#ifndef CPPARGPARSE_ARGUMENTS_VECTOR_H
#define CPPARGPARSE_ARGUMENTS_VECTOR_H

#include <algorithm>
#include <sstream>
#include <vector>

#include <cppargparse/algorithm.h>
#include <cppargparse/errors.h>
#include <cppargparse/globals.h>
#include <cppargparse/types.h>

#include "default.h"


namespace cppargparse {


template <typename T>
/**
 * @brief The argument struct for the std::vector<T> type.
 */
struct argument<std::vector<T>>
{
    /**
     * @brief Try to parse and return the integer value for an argument. Throw a #parser::ParserException on failure.
     *
     * @param key_it The argument key iterator.
     *
     * @return The parsed integer value for an argument on success or throw a #parser::ParserException on failure.
     */
    static const std::vector<T> parse(const types::CommandLineArgument_t &cmdarg)
    {
        auto options = algorithm::collect_arg_values(cmdarg);
        std::vector<T> values;

        for (auto option : options)
        {
            values.emplace_back(argument<T>::convert(option));
        }

        return values;
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_VECTOR_H
