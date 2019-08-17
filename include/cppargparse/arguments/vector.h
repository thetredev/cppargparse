#ifndef CPPARGPARSE_ARGUMENTS_VECTOR_H
#define CPPARGPARSE_ARGUMENTS_VECTOR_H

#include <vector>

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
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &cmdargs)
    {
        auto options = get_option_values(cmd, cmdarg, cmdargs);
        std::vector<T> values;

        for (auto option : options)
        {
            values.emplace_back(argument<T>::convert(cmd, option, cmdargs));
        }

        return values;
    }


    static types::CommandLineArguments_t get_option_values(
            const types::CommandLine_t &cmd,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &cmdargs)
    {
        types::CommandLineArguments_t values;

        for (auto cmdarg_value = std::next(cmdarg); cmdarg_value != cmd.end(); ++cmdarg_value)
        {
            if (cmdargs.find(*cmdarg_value) != cmdargs.cend())
            {
                break;
            }

            values.emplace_back(cmdarg_value);
        }

        return values;
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_VECTOR_H
