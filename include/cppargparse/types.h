#ifndef CPPARGPARSE_TYPES_H
#define CPPARGPARSE_TYPES_H

#include <map>
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
 * A std::vector of command line argument iterator positions.
 */
typedef std::vector<CommandLineArgument_t> CommandLineArguments_t;


/**
 * @brief The command line arguments map type.
 *
 * Key:     argument string
 * Value:   command line argument iterator position.
 */
typedef std::map<std::string, CommandLineArgument_t> CommandLineArgumentsMap_t;


} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPES_H
