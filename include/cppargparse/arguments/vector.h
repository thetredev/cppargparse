#ifndef CPPARGPARSE_ARGUMENTS_VECTOR_H
#define CPPARGPARSE_ARGUMENTS_VECTOR_H

#include <vector>

#include <cppargparse/algorithm.h>
#include <cppargparse/types.h>

#include "default.h"


namespace cppargparse {


template <typename T>
/**
 * @brief The argument struct for the std::vector<T> type.
 *
 * @tparam T The argument vector type.
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
    static const std::vector<T> parse(
            const types::CommandLine_t &cmd,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &cmdargs)
    {
        auto positions = get_option_positions(cmd, position, cmdargs);
        std::vector<T> values;

        for (auto position : positions)
        {
            values.emplace_back(argument<T>::convert(cmd, position, cmdargs));
        }

        return values;
    }


    static types::CommandLinePositions_t get_option_positions(
            const types::CommandLine_t &cmd,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &cmdargs)
    {
        types::CommandLinePositions_t positions;

        for (auto current = std::next(position); current != cmd.end(); ++current)
        {
            if (algorithm::find_arg(cmdargs, *current) != cmdargs.cend())
            {
                break;
            }

            positions.emplace_back(current);
        }

        return positions;
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_VECTOR_H
