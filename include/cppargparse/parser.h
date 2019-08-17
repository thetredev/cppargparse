#ifndef CPPARGPARSE_PARSER_H
#define CPPARGPARSE_PARSER_H

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
     */
    explicit ArgumentParserBase(int argc, char *argv[])
        : m_cmd(types::CommandLine_t(argv, argv + argc))
        , m_cmdargs()
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
                    id, std::string(), std::string(), algorithm::find_arg_position(m_cmd, id)
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
                    id, id_alt, std::string(), algorithm::find_arg_position(m_cmd, id)
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
                    id, id_alt, description, algorithm::find_arg_position(m_cmd, id)
        });
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
        return algorithm::find_arg_position(m_cmd, id) != m_cmd.cend();
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


protected:
    types::CommandLine_t m_cmd;
    types::CommandLineArguments_t m_cmdargs;
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
     */
    explicit ArgumentParser(int argc, char *argv[])
        : ArgumentParserBase(argc, argv)
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
        auto it = algorithm::find_arg(m_cmdargs, id);

        if (it == m_cmdargs.cend())
        {
            std::ostringstream message;
            message << "Cannot find argument: " << id;

            throw errors::CommandLineArgumentError(message.str());
        }

        // return the stored arg value
        return argument<T>::parse(m_cmd, it->position, m_cmdargs);
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
};


} // namespace cppargparse::parser

#endif // CPPARGPARSE_PARSER_H
