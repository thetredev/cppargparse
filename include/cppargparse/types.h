#ifndef CPPARGPARSE_TYPES_H
#define CPPARGPARSE_TYPES_H

#include <string>
#include <vector>


namespace cppargparse::types {


/**
 * @brief The command line type.
 *
 * Example: "-t 5 -o output.txt"
 */
typedef std::vector<std::string> CommandLine_t;


/**
 * @brief The command line argument type.
 *
 * Example:
 *     cmd args: "-t 5 -o output.txt"
 *     argument iterator at position 0: "-t", 1: "5", 3: "-o", 4: "output.txt"
 */
typedef CommandLine_t::const_iterator CommandLineArgument_t;


/**
 * @brief The command line arguments type.
 *
 * Options can be switches (with a value and/or default value) or flags (boolean switches without values).
 *
 * Example:
 *    cmd args: "-t 5 -o output.txt"
 *    options:  cmd args iterator positions of -t, -o
 */
typedef std::vector<CommandLineArgument_t> CommandLineArguments_t;


/**
 * @brief The command line option type.
 *
 * Alias for CommandLineArguments_t to indicate argument options instead of arguments themselves.
 */
typedef CommandLineArguments_t CommandLineOptions_t;


} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPES_H
