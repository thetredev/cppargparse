#ifndef CPPARGPARSE_PARSER_BASE_H
#define CPPARGPARSE_PARSER_BASE_H

#include <sstream>

#include <cppargparse/algorithm.h>
#include <cppargparse/types.h>


namespace cppargparse {
namespace parser {


/**
 * @brief Base class for the argument parser.
 */
class ArgumentParserBase
{
public:
    /**
     * @brief c'tor
     *
     * @param argc The command line argument count.
     * @param argv The command line argument array.
     * @param application_description The application description.
     */
    explicit ArgumentParserBase(int argc, char *argv[], const std::string &application_description)
        : m_cmd(types::CommandLine_t(argv, argv + argc))
        , m_cmdargs()
        , m_application_description(application_description)
    {
    }

    /**
     * @brief d'tor
     *
     * Clean up storage for the command line and the command line argument map.
     */
    ~ArgumentParserBase()
    {
        m_cmd.clear();
        m_cmdargs.clear();
    }


    /**
     * @brief Add an argument to the command line arguments list.
     *
     * @param cmdarg The command line argument struct object.
     */
    void add_arg(const types::CommandLineArgument_t &cmdarg)
    {
        m_cmdargs.emplace_back(cmdarg);
    }

    /**
     * @brief Add an argument to the command line arguments list.
     *
     * @param id The argument ID.
     *
     * @return The generated command line argument.
     */
    const types::CommandLineArgument_t add_arg(const std::string &id)
    {
        const types::CommandLineArgument_t arg {
            id, std::string(), std::string(),
            algorithm::find_arg_position(m_cmd, id, std::string())
        };

        add_arg(arg);
        return arg;
    }

    /**
     * @brief Add an argument to the command line arguments list.
     *
     * @param id The argument ID.
     * @param id_alt The alternative argument ID.
     *
     * @return The generated command line argument.
     */
    const types::CommandLineArgument_t add_arg(const std::string &id, const std::string &id_alt)
    {
        const types::CommandLineArgument_t arg {
            id, id_alt, std::string(),
            algorithm::find_arg_position(m_cmd, id, id_alt)
        };

        add_arg(arg);
        return arg;
    }

    /**
     * @brief Add an argument to the command line arguments list.
     *
     * @param id The argument ID.
     * @param id_alt The alternative argument ID.
     * @param description The argument description.
     *
     * @return The generated command line argument.
     */
    const types::CommandLineArgument_t add_arg(const std::string &id, const std::string &id_alt, const std::string &description)
    {
        const types::CommandLineArgument_t arg {
            id, id_alt, description,
            algorithm::find_arg_position(m_cmd, id, id_alt)
        };

        add_arg(arg);
        return arg;
    }


    /**
     * @brief Add default help argument: -h, --help
     *
     * @return The generated command line argument.
     */
    const types::CommandLineArgument_t add_help()
    {
        return add_arg("-h", "--help", "Display this information");
    }


    /**
     * @brief Return whether the command line contains an argument string.
     *
     * @param cmdarg The command line argument.
     *
     * @return Whether the command line contains an argument string.
     */
    inline bool get_flag(const types::CommandLineArgument_t &cmdarg)
    {
        return algorithm::find_arg_position(m_cmd, cmdarg.id, cmdarg.id_alt) != m_cmd.cend();
    }

    template <typename T>
    /**
     * @brief Stub method for returning an argument value.
     *
     * @tparam T The argument type. Must be non-abstract and have a default constructor.
     *
     * @return A new instance of T.
     */
    inline const T get_option(const types::CommandLineArgument_t &)
    {
        return T();
    }

    template <typename T>
    /**
     * @brief Stub method for returning an argument value.
     *
     * @tparam T The argument type. Is ignored in this case.
     *
     * @param default_value The default value.
     *
     * @return The default value.
     */
    inline const T get_option(const types::CommandLineArgument_t &, const T &default_value)
    {
        return default_value;
    }


    /**
     * @brief Generate and return the usage string.
     *
     * @return The generated usage string.
     */
    const std::string usage() const
    {
        // Find the maximum (argument ID, argument alternative ID) length
        size_t max_id_length = 0;

        for (const auto &cmdarg : m_cmdargs)
        {
            const size_t id_length = cmdarg.id.size() + cmdarg.id_alt.size();

            if (id_length > max_id_length)
            {
                max_id_length = id_length;
            }
        }

        // Add 3 more spaces
        max_id_length += 3;


        // Generate the usage string
        std::ostringstream usage_string;
        usage_string << "Usage: " << m_application_description << '\n' << '\n';

        for (const auto &cmdarg : m_cmdargs)
        {
            usage_string << ' ' << ' ' << cmdarg.id;

            if (!cmdarg.id_alt.empty())
            {
                usage_string << '|' << cmdarg.id_alt;
            }

            for (size_t i = 0; i < max_id_length; ++i)
            {
                usage_string << ' ';
            }

            if (!cmdarg.description.empty())
            {
                usage_string << cmdarg.description;
            }

            usage_string << '\n';
        }

        return usage_string.str();
    }


protected:
    /// The command line
    types::CommandLine_t m_cmd;

    /// The command line arguments
    types::CommandLineArguments_t m_cmdargs;


private:
    /// The application description
    const std::string m_application_description;
};


} // namespace parser
} // namespace cppargparse

#endif // CPPARGPARSE_PARSER_BASE_H
