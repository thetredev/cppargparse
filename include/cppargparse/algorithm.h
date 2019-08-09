#ifndef CPPARGPARSE_ALGORITHM_H
#define CPPARGPARSE_ALGORITHM_H

#include <vector>

#include "errors.h"
#include "globals.h"
#include "types.h"


namespace cppargparse::algorithm {


/**
 * @brief Put command line arguments into #g_cmdargs.
 *
 * @param argc The length of the command-line arguments array.
 * @param argv The command line arguments array.
 */
void collect_cmdargs(size_t argc, const char *argv[])
{
    const types::CommandLine_t args(argv, argv + argc);

    g_cmdargs.assign(args.cbegin(), args.cend());
}


/**
 * @brief Collect all values tied to an argument as an std::vector.
 *
 * @param cmdarg The command line argument iterator.
 *
 * @return An std::vector of argument value iterators tied to an argument key.
 */
const types::CommandLineArguments_t collect_arg_values(const types::CommandLineArgument_t &cmdarg)
{
    types::CommandLineArguments_t values;

    for (auto cmdarg_value = std::next(cmdarg); cmdarg_value != g_cmdargs.end(); ++cmdarg_value)
    {
        auto option = std::find(g_options.cbegin(), g_options.cend(), cmdarg_value);

        if (option != g_options.cend())
        {
            break;
        }

        values.emplace_back(cmdarg_value);
    }

    return values;
}


/**
 * @brief Find an argument key within #g_cmdargs.
 *
 * @param The argument key to look for.
 *
 * @return An argument container list iterator at the key position.
 */
static const types::CommandLineArgument_t find_cmdarg(const std::string &arg)
{
    auto cmdarg = std::find(g_cmdargs.cbegin(), g_cmdargs.cend(), arg);

    if (cmdarg == g_cmdargs.cend())
    {
        std::ostringstream message;
        message << "Couldn't find argument '" << arg << "'.";

        throw errors::CommandLineArgumentError(message.str());
    }

    return cmdarg;
}


} // namespace cppargparse::algorithm

#endif // CPPARGPARSE_ALGORITHM_H
