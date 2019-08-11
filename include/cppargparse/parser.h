#ifndef CPPARGPARSE_PARSER_H
#define CPPARGPARSE_PARSER_H

#include <algorithm>
#include <sstream>

#include <cppargparse/arguments.h>
#include <cppargparse/types.h>

#include "errors.h"


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
     * @brief Add an argument to the command line argument map.
     *
     * @param arg The argument string to look for.
     */
    void add_arg(const std::string &arg)
    {
        m_cmdargs[arg] = find_cmdarg(arg);
    }


    /**
     * @brief Return whether the command line contains an argument string.
     *
     * @param arg The argument string to look for.
     *
     * @return Whether the command line contains an argument string.
     */
    inline bool get_flag(const std::string &arg)
    {
        return find_cmdarg(arg) != m_cmd.cend();
    }


    template <typename T>
    /**
     * @brief Stub method for returning an argument value.
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
     * @param default_value The default value.
     *
     * @return The default value.
     */
    inline const T get_option(const std::string &, const T &default_value)
    {
        return default_value;
    }


protected:
    types::CommandLineArgument_t find_cmdarg(const std::string &arg)
    {
        return std::find(m_cmd.cbegin(), m_cmd.cend(), arg);
    }


protected:
    types::CommandLine_t m_cmd;
    types::CommandLineArgumentsMap_t m_cmdargs;
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
     * @param arg The argument string.
     *
     * @return The argument value of type T.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found.
     */
    inline const T get_option(const std::string &arg)
    {
        if (m_cmdargs.find(arg) == m_cmdargs.cend())
        {
            std::ostringstream message;
            message << "Cannot find argument: " << arg;

            throw errors::CommandLineArgumentError(message.str());
        }

        // return the stored arg value
        return argument<T>::parse(m_cmd, m_cmdargs[arg], m_cmdargs);
    }


    template <typename T>
    /**
     * @brief Return an argument value.
     *
     * @param arg The argument string.
     * @param default_value The default argument value of type T.
     *
     * @return The argument value of type T or the default value if the argument cannot be found.
     * @throws #cppargparse::errors::CommandLineArgumentError if the argument cannot be found
     */
    inline const T get_option(const std::string &arg, const T &default_value)
    {
        try
        {
            return get_option<T>(arg);
        }

        catch (const errors::Error &)
        {
            return default_value;
        }
    }
};


} // namespace cppargparse::parser

#endif // CPPARGPARSE_PARSER_H
