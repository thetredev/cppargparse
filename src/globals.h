#ifndef CPPARGPARSE_MACROS_H
#define CPPARGPARSE_MACROS_H

#include "types.h"


namespace cppargparse {


/**
 * @brief The global argument container list.
 *
 * @todo Make this read-only but updatable.
 */
static types::ArgumentList_t g_args;


} // namespace cppargparse

#endif // CPPARGPARSE_MACROS_H
