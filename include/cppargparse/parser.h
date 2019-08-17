#ifndef CPPARGPARSE_PARSER_H
#define CPPARGPARSE_PARSER_H

#include <functional>
#include <sstream>

#include "algorithm.h"
#include "arguments.h"
#include "errors.h"
#include "types.h"


namespace cppargparse::parser {


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
     */
    void add_arg(const std::string &id)
    {
        add_arg(types::CommandLineArgument_t {
                    id, std::string(), std::string(),
                    algorithm::find_arg_position(m_cmd, id, std::string())
        });
    }

    /**
     * @brief Add an argument to the command line arguments list.
     *
     * @param id The argument ID.
     * @param id_alt The alternative argument ID.
     */
    void add_arg(const std::string &id, const std::string &id_alt)
    {
        add_arg(types::CommandLineArgument_t {
                    id, id_alt, std::string(),
                    algorithm::find_arg_position(m_cmd, id, id_alt)
        });
    }

    /**
     * @brief Add an argument to the command line arguments list.
     *
     * @param id The argument ID.
     * @param id_alt The alternative argument ID.
     * @param description The argument description.
     */
    void add_arg(const std::string &id, const std::string &id_alt, const std::string &description)
    {
        add_arg(types::CommandLineArgument_t {
                    id, id_alt, description,
                    algorithm::find_arg_position(m_cmd, id, id_alt)
        });
    }


    /**
     * @brief Add default help argument: -h, --help
     */
    void add_help()
    {
        add_arg("-h", "--help", "Display this information");
    }


    /**
     * @brief Return whether the command line contains an argument string.
     *
     * @param id The argument ID.
     *
     * @return Whether the command line contains an argument string.
     */
    inline bool get_flag(const std::string &id)
    {
        return algorithm::find_arg_position(m_cmd, id, id) != m_cmd.cend();
    }

    template <typename T>
    /**
     * @brief Stub method for returning an argument value.
     *
     * @tparam T The argument type. Must be non-abstract and have a default constructor.
     *
     * @return A new instance of T.
     */
    inline const T get_option(const std::string &)
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
    inline const T get_option(const std::string &, const T &default_value)
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
    types::CommandLine_t m_cmd;
    types::CommandLineArguments_t m_cmdargs;


private:
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
     * @brief Return an argument value.
     *
     * @tparam T The argument type. argument::parse() and argument::convert() must be implemented for T.
     *
     * @param id The argument ID. Can also be the argument's alternative ID.
     *
     * @return The argument value of type T.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found.
     */
    inline const T get_option(const std::string &id)
    {
        if (algorithm::find_arg(m_cmdargs, id) == m_cmdargs.cend())
        {
            throw cmdarg_invalid_error(id);
        }


        auto it = algorithm::find_arg_position(m_cmd, id, id);

        if (it == m_cmd.cend())
        {
            throw cmdarg_not_found_error(id);
        }


        // return the stored arg value
        return argument<T>::parse(m_cmd, it, m_cmdargs);
    }


    template <typename T>
    /**
     * @brief Return an argument value.
     *
     * @tparam T The argument type. argument::parse() and argument::convert() must be implemented for T.
     *
     * @param id The argument string. Can also be the argument's alternative ID.
     * @param default_value The default argument value of type T.
     *
     * @return The argument value of type T or the default value if the argument cannot be found.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found
     */
    inline const T get_option(const std::string &id, const T &default_value)
    {
        try
        {
            return get_option<T>(id);
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
    void add_flag_with_callback(const std::string &id, const std::function<void(const ArgumentParser &)> &callback)
    {
        add_arg(id);

        if (get_flag(id))
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
    void add_flag_with_callback(const std::string &id, const std::string &id_alt, const std::function<void(const ArgumentParser &)> &callback)
    {
        add_arg(id, id_alt);

        if (get_flag(id) || get_flag(id_alt))
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
        add_arg(id, id_alt, description);

        if (get_flag(id) || get_flag(id_alt))
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
        add_help();

        if (get_flag("-h") || get_flag("--help"))
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
     *
     * @throws #errors::CommandLineArgumentError if the arg wasn't found in the command line.
     * @throws #errors::CommandLineOptionError if no value has been found for the argument.
     */
    void add_arg_with_callback(const std::string &id, const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        add_arg(id);

        try
        {
            callback(*this, get_option<T>(id));
        }

        catch (errors::CommandLineArgumentError &error)
        {
            throw errors::CommandLineArgumentError(error);
        }
        catch (errors::CommandLineOptionError &error)
        {
            throw errors::CommandLineOptionError(error);
        }
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
     *
     * @throws #errors::CommandLineArgumentError if the arg wasn't found in the command line.
     * @throws #errors::CommandLineOptionError if no value has been found for the argument.
     */
    void add_arg_with_callback(const std::string &id, const std::string &id_alt,
                               const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        add_arg(id, id_alt);

        try
        {
            callback(*this, get_option<T>(find_cmd_id(id, id_alt, true)));
        }
        catch (errors::CommandLineOptionError &error)
        {
            throw errors::CommandLineOptionError(error);
        }
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
     *
     * @throws #errors::CommandLineArgumentError if the arg wasn't found in the command line.
     * @throws #errors::CommandLineOptionError if no value has been found for the argument.
     */
    void add_arg_with_callback(const std::string &id, const std::string &id_alt, const std::string &description,
                                       const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        add_arg(id, id_alt, description);

        try
        {
            callback(*this, get_option<T>(find_cmd_id(id, id_alt, true)));
        }
        catch (errors::CommandLineOptionError &error)
        {
            throw errors::CommandLineOptionError(error);
        }
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
        add_arg(id);

        callback(*this, get_option<T>(id, default_value));
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
        add_arg(id, id_alt);

        callback(*this, get_option<T>(find_cmd_id(id, id_alt, false), default_value));
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
    void add_arg_with_callback_default(const std::string &id, const std::string &id_alt, const std::string &description,
                                       const T &default_value, const std::function<void(const ArgumentParser &, const T &)> &callback)
    {
        add_arg(id, id_alt, description);

        callback(*this, get_option<T>(find_cmd_id(id, id_alt, false), default_value));
    }


private:
    errors::CommandLineArgumentError cmdarg_not_found_error(const std::string &id)
    {
        std::ostringstream message;
        message << "Cannot find argument: " << id;

        return errors::CommandLineArgumentError(message.str());
    }

    errors::CommandLineArgumentError cmdarg_invalid_error(const std::string &id)
    {
        std::ostringstream message;
        message << "Invalid argument: " << id;

        return errors::CommandLineArgumentError(message.str());
    }


    const std::string find_cmd_id(const std::string &id, const std::string &id_alt, const bool throw_error)
    {
        if (get_flag(id))
        {
            return id;
        }

        if (get_flag(id_alt))
        {
            return id_alt;
        }

        if (throw_error)
        {
            throw cmdarg_not_found_error(id);
        }
        else
        {
            return "____CPPARGPARSE_INVALID_ARGUMENT_ID";
        }
    }
};


} // namespace cppargparse::parser

#endif // CPPARGPARSE_PARSER_H
