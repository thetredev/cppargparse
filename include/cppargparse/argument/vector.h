#ifndef CPPARGPARSE_ARGUMENT_VECTOR_H
#define CPPARGPARSE_ARGUMENT_VECTOR_H

#include <vector>

#include <cppargparse/algorithm.h>
#include <cppargparse/cmd.h>

#include "argument.h"


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
     * @brief Try to parse and return all typed values for the vector argument.
     *
     * @param cmd The command line.
     * @param position The command line argument iterator.
     * @param cmdargs The command line arguments.
     *
     * @return All typed values for the vector argument.
     */
    static const std::vector<T> parse(
            const cmd::CommandLine_t &cmd,
            const cmd::CommandLinePosition_t &position,
            const cmd::CommandLineArguments_t &cmdargs)
    {
        auto positions = algorithm::get_option_positions(cmd, position, cmdargs);
        std::vector<T> values;

        for (auto position : positions)
        {
            values.emplace_back(argument<T>::convert(cmd, position, cmdargs));
        }

        return values;
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENT_VECTOR_H
