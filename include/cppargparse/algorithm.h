#ifndef CPPARGPARSE_ALGORITHM_H
#define CPPARGPARSE_ALGORITHM_H

#include <algorithm>

#include "types.h"


namespace cppargparse::algorithm {


/**
 * @brief Find an argument by its ID.
 *
 * @param cmdargs The command line arguments to lookup the argument ID.
 * @param id The argument ID. Can also be the argument's alterinative ID.
 *
 * @return The command line arguments iterator position of the argument.
 */
types::CommandLineArgumentPosition_t find_arg(const types::CommandLineArguments_t &cmdargs, const std::string &id)
{
    for (auto it = cmdargs.cbegin(); it != cmdargs.cend(); ++it)
    {
        if (it->id == id || it->id_alt == id)
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
 * @param id The argument ID. Can also be the argument's alternative ID.
 *
 * @return The command line iterator position of the argument.
 */
types::CommandLinePosition_t find_arg_position(const types::CommandLine_t &cmd, const std::string &id)
{
    return std::find(cmd.cbegin(), cmd.cend(), id);
}


} // namespace cppargparse::algorithm

#endif // CPPARGPARSE_ALGORITHM_H
