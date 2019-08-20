#ifndef CPPARGPARSE_PARSER_H
#define CPPARGPARSE_PARSER_H

#include <functional>
#include <sstream>

#include "algorithm.h"
#include "arguments.h"
#include "errors.h"
#include "types.h"


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


/**
 * @brief The argument parser class.
 *
 * Used as an interface between the argument value conversion operations and the outside world.
 */
class ArgumentParser : public ArgumentParserBase
{
public:
    /**
     * @brief c'tor
     *
     * @param argc The command line argument count.
     * @param argv The command line argument array.
     * @param application_description The application description.
     */
    explicit ArgumentParser(int argc, char *argv[], const std::string &application_description)
        : ArgumentParserBase(argc, argv, application_description)
    {
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
    inline const T get_option(const types::CommandLineArgument_t &cmdarg)
    {
        if (cmdarg.position == m_cmd.cend())
        {
            std::ostringstream message;
            message << "Cannot find argument: " << cmdarg.id;

            throw errors::CommandLineArgumentError(message.str());
        }

        return argument<T>::parse(m_cmd, cmdarg.position, m_cmdargs);
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
    inline const T get_option(const types::CommandLineArgument_t &cmdarg, const T &default_value)
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
};


} // namespace parser
} // namespace cppargparse

#endif // CPPARGPARSE_PARSER_H
