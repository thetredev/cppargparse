#ifndef CPPARGPARSE_ARGUMENTS_CONTAINER_H
#define CPPARGPARSE_ARGUMENTS_CONTAINER_H

#include <list>
#include <vector>

#include <cppargparse/algorithm.h>
#include <cppargparse/cmd.h>

#include "argument.h"


#define CPPARGPARSE_CONTAINER_ARGUMENT(container_type) \
template <typename T> \
struct argument<container_type<T>> { \
\
    static const container_type<T> parse( \
            const cmd::CommandLine_t &cmd, \
            const cmd::CommandLinePosition_t &position, \
            const cmd::CommandLineArguments_t &cmdargs) \
    { \
        auto positions = algorithm::get_option_positions(cmd, position, cmdargs); \
        container_type<T> values; \
\
        for (auto position : positions) \
        { \
            values.emplace_back(argument<T>::convert(cmd, position, cmdargs)); \
        } \
\
        return values; \
    } \
}


namespace cppargparse {


CPPARGPARSE_CONTAINER_ARGUMENT(std::list);
CPPARGPARSE_CONTAINER_ARGUMENT(std::vector);


} // namespace cppargparse

#endif // CPPARGPARSE_ARGUMENTS_CONTAINER_H
