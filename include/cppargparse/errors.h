#ifndef CPPARGPARSE_ERRORS_H
#define CPPARGPARSE_ERRORS_H

#include <stdexcept>


namespace cppargparse {
namespace errors {


/**
 * @brief Base error class.
 */
class Error : public std::runtime_error
{
public:
    /**
     * @brief c'tor
     *
     * @param message The error message.
     */
    explicit Error(const std::string &message)
        : std::runtime_error(std::string("Error: ") + message)
    {
    }
};


/**
 * @brief Error class for command line argument errors.
 */
class CommandLineArgumentError: public Error
{
public:
    /**
     * @brief c'tor
     *
     * @param message The error message.
     */
    explicit CommandLineArgumentError(const std::string &message)
        : Error(message)
    {
    }
};


/**
 * @brief Error class for command line option errors.
 */
class CommandLineOptionError : public Error
{
public:
    /**
     * @brief c'tor
     *
     * @param message The error message.
     */
    explicit CommandLineOptionError(const std::string &message)
        : Error(message)
    {
    }
};


} // namespace errors
} // namespace cppargparse

#endif // CPPARGPARSE_ERRORS_H
