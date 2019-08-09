#ifndef CPPARGPARSE_GLOBALS_H
#define CPPARGPARSE_GLOBALS_H

#include <algorithm>
#include <sstream>

#include "types.h"


namespace cppargparse {


/**
 * @brief The global list of command line arguments.
 *
 * @todo Make this read-only but updatable.
 */
static types::CommandLine_t g_cmdargs;

/**
 * @brief The global list of command line options.
 *
 * @todo Make this read-only but updatable.
 */
static types::CommandLineOptions_t g_options;


} // namespace cppargparse

#endif // CPPARGPARSE_GLOBALS_H
