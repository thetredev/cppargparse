#ifndef CPPARGPARSE_PARSER_ERRORS_H
#define CPPARGPARSE_PARSER_ERRORS_H

#include <stdexcept>



namespace cppargparse::parser::errors {


/**
 * @brief The ParserException class acts as an interface for parsing-related errors.
 */
class ParserError : public std::runtime_error
{
public:
    /**
     * @brief c'tor
     *
     * @param message The error message.
     */
    explicit ParserError(const std::string &message)
        : std::runtime_error(std::string("Error: ") + message)
    {
    }
};


} // namespace cppargparse::parser::errors

#endif // CPPARGPARSE_PARSER_ERRORS_H
