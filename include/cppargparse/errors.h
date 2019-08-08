#ifndef CPPARGPARSE_PARSER_ERRORS_H
#define CPPARGPARSE_PARSER_ERRORS_H

#include <stdexcept>



namespace cppargparse::errors {


/**
 * @brief The Error class acts as an interface for library-related errors.
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
 * @brief The ParserError class acts as an interface for parsing-related errors.
 */
class ParserError : public Error
{
public:
    /**
     * @brief c'tor
     *
     * @param message The error message.
     */
    explicit ParserError(const std::string &message)
        : Error(message)
    {
    }
};


/**
 * @brief The ArgumentKeyNotFoundError class acts as an interface for argument key errors.
 */
class ArgumentKeyError: public Error
{
public:
    /**
     * @brief c'tor
     *
     * @param message The error message.
     */
    explicit ArgumentKeyError(const std::string &message)
        : Error(message)
    {
    }
};


} // namespace cppargparse::parser::errors

#endif // CPPARGPARSE_PARSER_ERRORS_H
