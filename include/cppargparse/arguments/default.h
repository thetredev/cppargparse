#ifndef CPPARGPARSE_ARGUMENTS_DEFAULT_H
#define CPPARGPARSE_ARGUMENTS_DEFAULT_H

#include <cppargparse/types.h>


namespace cppargparse {


template <typename T>
/**
 * @brief The default argument struct. Provides stub methods returning stub values.
 */
struct argument
{
    /**
     * @brief Stub parse method for any type.
     *
     * @return A new instance of the template type.
     */
    static const T parse(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &,
            const types::CommandLineArgumentsMap_t &)
    {
        return T();
    }


    /**
     * @brief Stub convert method for any type.
     *
     * @return A new instance of the template type.
     */
    static const T convert(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &,
            const types::CommandLineArgumentsMap_t &)
    {
        return T();
    }


    /**
     * @brief Stub error message.
     *
     * @return An empty C-style string.
     */
    static const char *error_message(const types::CommandLineArgument_t &)
    {
        return "";
    }
};


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_DEFAULT_H
