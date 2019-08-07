#ifndef CPPARGPARSE_GLOBALS_H
#define CPPARGPARSE_GLOBALS_H

#include <algorithm>
#include <sstream>

#include "types.h"


namespace cppargparse {


/**
 * @brief The global argument container list.
 *
 * @todo Make this read-only but updatable.
 */
static types::ArgumentList_t g_args;

/**
 * @brief The global key list.
 *
 * @todo Make this read-only but updatable.
 */
static types::ArgumentKeyList_t g_keys;


} // namespace cppargparse

#endif // CPPARGPARSE_GLOBALS_H
