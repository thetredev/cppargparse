#ifndef CPPARGPARSE_ALGORITHM_H
#define CPPARGPARSE_ALGORITHM_H

/**
  @file cppargparse/algorithm.h
  @brief Static command line related algorithm functions.
 */


#include <algorithm>

#include "cmd.h"


namespace cppargparse {
namespace algorithm {


/**
 * @brief Find an argument by its ID.
 *
 * @param cmdargs The command line arguments to lookup the argument ID.
 * @param id The argument ID. Can also be the argument's alterinative ID.
 *
 * @return The command line arguments iterator position of the argument.
 */
cmd::CommandLineArgumentPosition_t find_arg(const cmd::CommandLineArguments_t &cmdargs, const std::string &id)
{
    for (auto it = cmdargs.cbegin(); it != cmdargs.cend(); ++it)
    {
        if (it->id() == id || it->id_alt() == id)
        {
            return it;
        }
    }

    return cmdargs.cend();
}


/**
 * @brief Find an argument's command line position by its ID.
 *
 * @param cmd The command line.
 * @param id The argument ID.
 * @param id_alt The argument alternative ID.
 *
 * @return The command line iterator position of the argument.
 */
cmd::CommandLinePosition_t find_arg_position(const cmd::CommandLine_t &cmd, const std::string &id, const std::string &id_alt)
{
    auto it = std::find(cmd.cbegin(), cmd.cend(), id);

    if (it == cmd.cend())
    {
        it = std::find(cmd.cbegin(), cmd.cend(), id_alt);
    }

    return it;
}


/**
 * @brief Return command line positions of an argument vector option.
 *
 * @param cmd The command line.
 * @param position The argument iterator position (start position).
 * @param cmdargs The command line arguments.
 *
 * @return Command line positions of an argument vector option.
 */
cmd::CommandLinePositions_t get_option_positions(
        const cmd::CommandLine_t &cmd,
        const cmd::CommandLinePosition_t &position,
        const cmd::CommandLineArguments_t &cmdargs)
{
    cmd::CommandLinePositions_t positions;

    for (auto current = std::next(position); current != cmd.end(); ++current)
    {
        if (find_arg(cmdargs, *current) != cmdargs.cend())
        {
            break;
        }

        positions.emplace_back(current);
    }

    return positions;
}


} // namespace algorithm
} // namespace cppargparse

#endif // CPPARGPARSE_ALGORITHM_H
