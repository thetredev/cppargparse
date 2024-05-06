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
 * @brief The command line argument class.
 */
class CommandLineArgument
{
public:
    CommandLineArgument() = delete;
    CommandLineArgument& operator= (const CommandLineArgument& command_line_argument);

    /**
     * @brief c'tor
     *
     * @param id The argument ID.
     * @param position The argument command line argument iterator position.
     */
    CommandLineArgument(
            const std::string &id,
            const CommandLinePosition_t &position
    )
        : CommandLineArgument(id, "", "", position)
    {
    }


    /**
     * @brief c'tor
     *
     * @param id The argument ID.
     * @param id_alt The alternative argument ID.
     * @param position The argument command line argument iterator position.
     */
    CommandLineArgument(
            const std::string &id,
            const std::string &id_alt,
            const CommandLinePosition_t &position
    )
        : CommandLineArgument(id, id_alt, "", position)
    {
    }


    /**
     * @brief c'tor
     *
     * @param id The argument ID.
     * @param id_alt The alternative argument ID.
     * @param description The argument description.
     * @param position The argument command line argument iterator position.
     */
    CommandLineArgument(
            const std::string &id,
            const std::string &id_alt,
            const std::string &description,
            const CommandLinePosition_t &position
    )
        : m_id(id)
        , m_id_alt(id_alt)
        , m_description(description)
        , m_position(position)
    {
    }


    /**
     * @brief Return the argument ID.
     *
     * @return The argument ID.
     */
    const std::string &id() const
    {
        return m_id;
    }


    /**
     * @brief Return the alternative argument ID.
     *
     * @return The alternative argument ID.
     */
    const std::string &id_alt() const
    {
        return m_id_alt;
    }


    /**
     * @brief Return the argument description.
     *
     * @return The argument description.
     */
    const std::string &description() const
    {
        return m_description;
    }


    /**
     * @brief Return the argument position.
     *
     * @return The argument position.
     */
    const CommandLinePosition_t &position() const
    {
        return m_position;
    }


private:
    /// The argument ID.
    /// Example: "-t"
    const std::string m_id;

    /// The alternative argument ID.
    /// Example: "--timeout"
    const std::string m_id_alt;

    /// The argument description.
    /// Example: "The timeout in seconds."
    const std::string m_description;

    /// The argument command line argument iterator position.
    /// Example: cmd_position for ("-t", "--timeout") is the argument iterator position 0.
    const CommandLinePosition_t m_position;
};


/**
 * @brief The command line arguments type.
 */
typedef std::vector<CommandLineArgument> CommandLineArguments_t;


/**
 * @brief The command line argument iterator position type.
 */
typedef CommandLineArguments_t::const_iterator CommandLineArgumentPosition_t;


} // namespace cmd
} // namespace cppargparse

#endif // CPPARGPARSE_CMD_H
