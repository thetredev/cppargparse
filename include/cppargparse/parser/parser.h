#ifndef CPPARGPARSE_PARSER_PARSER_H
#define CPPARGPARSE_PARSER_PARSER_H

#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>

#include <cppargparse/arguments.h>
#include <cppargparse/errors.h>
#include <cppargparse/types.h>

#include "base.h"


namespace cppargparse {
namespace parser {


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
     * @brief Return the positional argument value of type T.
     *
     * @tparam T The argument type. argument::convert() must be implemented for T.
     *
     * @param positional The positional command line argument.
     *
     * @return The argument value of type T.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found.
     */
    inline const T get_positional(const types::CommandLineArgument_t &positional)
    {
        if (positional.position == m_cmd.cend())
        {
            const auto positional_it = std::find(m_positionals.cbegin(), m_positionals.cend(), positional);
            const int positional_index = std::distance(m_positionals.cbegin(), positional_it);

            std::ostringstream message;
            message << "Cannot find positional argument #" << positional_index + 1;

            throw errors::CommandLineArgumentError(message.str());
        }

        return argument<T>::convert(m_cmd, positional.position, m_cmdargs);
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

#endif // CPPARGPARSE_PARSER_PARSER_H
