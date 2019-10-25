#ifndef CPPARGPARSE_PARSER_PARSER_H
#define CPPARGPARSE_PARSER_PARSER_H

#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>

#include <cppargparse/arguments.h>
#include <cppargparse/cmd.h>
#include <cppargparse/errors.h>


namespace cppargparse {
namespace parser {


/**
 * @brief The argument parser class.
 *
 * Used as an interface between the argument value conversion operations and the outside world.
 */
class ArgumentParser
{
public:
    /**
     * @brief c'tor
     *
     * @param argc The command line argument count.
     * @param argv The command line argument array.
     * @param application_description The application description.
     */
    explicit ArgumentParser(int argc, char *argv[], const std::string &description)
        : m_cmd(cmd::CommandLine_t(argv, argv + argc))
        , m_cmdargs()
        , m_positionals()
        , m_description(description)
    {
    }


    /**
     * @brief d'tor
     *
     * Clean up storage for the command line and the command line argument map.
     */
    ~ArgumentParser()
    {
        m_cmd.clear();
        m_cmdargs.clear();
    }


    /**
     * @brief Add a positional argument which is neither a flag nor an option.
     *
     * The argument position is the command line iterator position
     * next the last command line argument's position (flag/option).
     *
     * If no flag/option argument has been stored yet, the position
     * will be the first command line iterator position.
     *
     * @param description The positional argument description.
     *
     * @return The generated command line argument.
     */
    const cmd::CommandLineArgument add_positional(const std::string &description)
    {
        cmd::CommandLineArgument arg {
            std::string(), std::string(), description,
            (m_cmdargs.size() > 0) ? std::next(std::prev(m_cmdargs.cend())->position()) : m_cmd.cbegin()
        };

        m_positionals.emplace_back(arg);
        return arg;
    }


    /**
     * @brief Add a positional argument which is neither a flag nor an option.
     *
     * The argument position is the command line iterator position
     * next the last command line argument's position (flag/option).
     *
     * If no flag/option argument has been stored yet, the position
     * will be the first command line iterator position.
     *
     * @return The generated command line argument.
     */
    const cmd::CommandLineArgument add_positional()
    {
        return add_positional(std::string());
    }


    /**
     * @brief Add an argument to the command line arguments list.
     *
     * @param cmdarg The command line argument struct object.
     */
    void add_arg(const cmd::CommandLineArgument &cmdarg)
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
    const cmd::CommandLineArgument add_arg(const std::string &id)
    {
        const cmd::CommandLineArgument arg {
            id, algorithm::find_arg_position(m_cmd, id, std::string())
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
    const cmd::CommandLineArgument add_arg(const std::string &id, const std::string &id_alt)
    {
        const cmd::CommandLineArgument arg {
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
    const cmd::CommandLineArgument add_arg(const std::string &id, const std::string &id_alt, const std::string &description)
    {
        const cmd::CommandLineArgument arg {
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
    const cmd::CommandLineArgument add_help()
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
    inline bool get_flag(const cmd::CommandLineArgument &cmdarg)
    {
        return algorithm::find_arg_position(m_cmd, cmdarg.id(), cmdarg.id_alt()) != m_cmd.cend();
    }


    template <typename T>
    /**
     * @brief Return the positional argument value of type T.
     *
     * @tparam T The argument type. argument::convert() must be implemented for T.
     *
     * @param positional The positional command line argument.
     *
     * @return The argument value of type T.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found.
     */
    inline const T get_positional(const cmd::CommandLineArgument &positional)
    {
        if (positional.position() == m_cmd.cend())
        {
            const auto positional_it = std::find(m_positionals.cbegin(), m_positionals.cend(), positional);
            const int positional_index = std::distance(m_positionals.cbegin(), positional_it);

            std::ostringstream message;
            message << "Cannot find positional argument #" << positional_index + 1;

            throw errors::CommandLineArgumentError(message.str());
        }

        return argument<T>::convert(m_cmd, positional.position(), m_cmdargs);
    }


    template <typename T>
    /**
     * @brief Return the argument value of type T.
     *
     * @tparam T The argument type. argument::parse() and argument::convert() must be implemented for T.
     *
     * @param cmdarg The command line argument.
     *
     * @return The argument value of type T.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found.
     */
    inline const T get_option(const cmd::CommandLineArgument &cmdarg)
    {
        if (cmdarg.position() == m_cmd.cend())
        {
            std::ostringstream message;
            message << "Cannot find argument: " << cmdarg.id();

            throw errors::CommandLineArgumentError(message.str());
        }

        return argument<T>::parse(m_cmd, cmdarg.position(), m_cmdargs);
    }


    template <typename T>
    /**
     * @brief Return an argument value.
     *
     * @tparam T The argument type. argument::parse() and argument::convert() must be implemented for T.
     *
     * @param cmdarg The command line argument.
     * @param default_value The default argument value of type T.
     *
     * @return The argument value of type T or the default value if the argument cannot be found.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found
     */
    inline const T get_option(const cmd::CommandLineArgument &cmdarg, const T &default_value)
    {
        try
        {
            return get_option<T>(cmdarg);
        }

        catch (const errors::Error &)
        {
            return default_value;
        }
    }


    /**
     * @brief Add a flag argument and call a callback when it has been passed to the command line.
     *
     * @param id The argument ID.
     * @param callback The callback to call when the flag has been passed to the command line.
     */
    void add_flag_with_callback(const std::string &id,
                                const std::function<void(const ArgumentParser &)> &callback)
    {
        auto cmdarg = add_arg(id);

        if (get_flag(cmdarg))
        {
            callback(*this);
        }
    }


    /**
     * @brief Add a flag argument and call a callback when it has been passed to the command line.
     *
     * @param id The argument ID.
     * @param id_alt The argument alternative ID.
     * @param callback The callback to call when the flag has been passed to the command line.
     */
    void add_flag_with_callback(const std::string &id, const std::string &id_alt,
                                const std::function<void(const ArgumentParser &)> &callback)
    {
        const auto cmdarg = add_arg(id, id_alt);

        if (get_flag(cmdarg))
        {
            callback(*this);
        }
    }


    /**
     * @brief Add a flag argument and call a callback when it has been passed to the command line.
     *
     * @param id The argument ID.
     * @param id_alt The argument alternative ID.
     * @param description The argument description.
     * @param callback The callback to call when the flag has been passed to the command line.
     */
    void add_flag_with_callback(const std::string &id, const std::string &id_alt, const std::string &description,
                                const std::function<void(const ArgumentParser &)> &callback)
    {
        const auto cmdarg = add_arg(id, id_alt, description);

        if (get_flag(cmdarg))
        {
            callback(*this);
        }
    }


    /**
     * @brief Add the default help argument (-h, --help) and call a callback when it has been passed to the command line.
     *
     * @param callback The callback to call when the flag has been passed to the command line.
     */
    void add_help_with_callback(const std::function<void(const ArgumentParser &)> &callback)
    {
        const auto cmdarg = add_help();

        if (get_flag(cmdarg))
        {
            callback(*this);
        }
    }


    template <typename T>
    /**
     * @brief Add an argument and call a callback with its value when it has been passed to the command line.
     *
     * @tparam T The argument value type.
     *
     * @param id The argument ID.
     * @param callback The callback to call with the argument's value when the argument has been passed to the command line.
     */
    void add_arg_with_callback(const std::string &id,
                               const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        callback(*this, get_option<T>(add_arg(id)));
    }


    template <typename T>
    /**
     * @brief Add an argument and call a callback with its value when it has been passed to the command line.
     *
     * @tparam T The argument value type.
     *
     * @param id The argument ID.
     * @param id_alt The argument alternative ID.
     * @param callback The callback to call with the argument's value when the argument has been passed to the command line.
     */
    void add_arg_with_callback(const std::string &id, const std::string &id_alt,
                               const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        callback(*this, get_option<T>(add_arg(id, id_alt)));
    }


    template <typename T>
    /**
     * @brief Add an argument and call a callback with its value when it has been passed to the command line.
     *
     * @tparam T The argument value type.
     *
     * @param id The argument ID.
     * @param id_alt The argument alternative ID.
     * @param description The argument description.
     * @param callback The callback to call with the argument's value when the argument has been passed to the command line.
     */
    void add_arg_with_callback(const std::string &id, const std::string &id_alt, const std::string &description,
                                       const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        callback(*this, get_option<T>(add_arg(id, id_alt, description)));
    }


    template <typename T>
    /**
     * @brief Add an argument and call a callback with its (default) value.
     *
     * @tparam T The argument value type.
     *
     * @param id The argument ID.
     * @param default_value The default value.
     * @param callback The callback to call with the argument's (default) value.
     */
    void add_arg_with_callback_default(const std::string &id, const T &default_value,
                                       const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        callback(*this, get_option<T>(add_arg(id), default_value));
    }


    template <typename T>
    /**
     * @brief Add an argument and call a callback with its (default) value.
     *
     * @tparam T The argument value type.
     *
     * @param id The argument ID.
     * @param id_alt The argument alternative ID.
     * @param default_value The default value.
     * @param callback The callback to call with the argument's (default) value.
     */
    void add_arg_with_callback_default(const std::string &id, const std::string &id_alt, const T &default_value,
                                       const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        callback(*this, get_option<T>(add_arg(id, id_alt), default_value));
    }


    template <typename T>
    /**
     * @brief Add an argument and call a callback with its (default) value.
     *
     * @tparam T The argument value type.
     *
     * @param id The argument ID.
     * @param id_alt The argument alternative ID.
     * @param description The argument description.
     * @param default_value The default value.
     * @param callback The callback to call with the argument's (default) value.
     */
    void add_arg_with_callback_default(const std::string &id, const std::string &id_alt,
                                       const std::string &description, const T &default_value,
                                       const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        callback(*this, get_option<T>(add_arg(id, id_alt, description), default_value));
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
            const size_t id_length = cmdarg.id().size() + cmdarg.id_alt().size();

            if (id_length > max_id_length)
            {
                max_id_length = id_length;
            }
        }

        // Add 3 more spaces
        max_id_length += 3;


        // Generate the usage string
        std::ostringstream usage_string;
        usage_string << "Usage: " << m_description << '\n' << '\n';

        for (const auto &cmdarg : m_cmdargs)
        {
            usage_string << ' ' << ' ' << cmdarg.id();

            if (!cmdarg.id_alt().empty())
            {
                usage_string << '|' << cmdarg.id_alt();
            }

            for (size_t i = 0; i < max_id_length; ++i)
            {
                usage_string << ' ';
            }

            if (!cmdarg.description().empty())
            {
                usage_string << cmdarg.description();
            }

            usage_string << '\n';
        }

        return usage_string.str();
    }


private:
    /// The command line
    cmd::CommandLine_t m_cmd;

    /// The command line arguments
    cmd::CommandLineArguments_t m_cmdargs;

    /// The positional command line arguments
    cmd::CommandLineArguments_t m_positionals;

    /// The application description
    const std::string m_description;
};


} // namespace parser
} // namespace cppargparse

#endif // CPPARGPARSE_PARSER_PARSER_H
