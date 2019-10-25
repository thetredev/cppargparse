#ifndef CPPARGPARSE_CMD_H
#define CPPARGPARSE_CMD_H

/**
  @file cppargparse/cmd.h
  @brief Global type definitions of command line related types.
 */


#include <string>
#include <vector>


namespace cppargparse {
namespace cmd {


/**
 * @brief The command line type.
 *
 * Example: "-t 5 -o output.txt"
 */
typedef std::vector<std::string> CommandLine_t;


/**
 * @brief The command line iterator position type.
 */
typedef CommandLine_t::const_iterator CommandLinePosition_t;


/**
 * @brief The command line iterator positions type.
 */
typedef std::vector<CommandLinePosition_t> CommandLinePositions_t;


/**
 * @brief The command line argument struct.
 */
struct CommandLineArgument_t
{
    /**
     * @brief The argument ID.
     *
     * Example: "-t"
     */
    const std::string id;

    /**
     * @brief The alternative argument ID.
     *
     * Example: "--timeout"
     */
    const std::string id_alt;

    /**
     * @brief The argument description.
     *
     * Example: "The timeout in seconds."
     */
    const std::string description;

    /**
     * @brief The argument command line argument iterator position.
     *
     * Example: cmd_position for ("-t", "--timeout") is the argument iterator position 0.
     */
    const CommandLinePosition_t position;
};


/**
 * @brief The command line arguments type.
 */
typedef std::vector<CommandLineArgument_t> CommandLineArguments_t;


/**
 * @brief The command line argument iterator position type.
 */
typedef CommandLineArguments_t::const_iterator CommandLineArgumentPosition_t;


} // namespace cmd
} // namespace cppargparse

#endif // CPPARGPARSE_CMD_H
