#ifndef CPPARGPARSE_ALGORITHM_H
#define CPPARGPARSE_ALGORITHM_H

#include <vector>

#include "errors.h"
#include "globals.h"
#include "types.h"


namespace cppargparse::algorithm {


/**
 * @brief Put command-line arguments into #g_args.
 *
 * @param argc The length of the command-line arguments array.
 * @param argv The command-line arguments array.
 */
void collect_cmdargs(int argc, char *argv[])
{
    const types::ArgumentList_t temp(argv, argv + argc);

    g_args.assign(temp.cbegin(), temp.cend());
}


/**
 * @brief Collect all values tied to an argument as an std::vector.
 *
 * @param key_it The argument key iterator.
 *
 * @return An std::vector of argument value iterators tied to an argument key.
 */
const std::vector<types::ArgumentList_t::const_iterator> collect_arg_values(const types::ArgumentList_t::const_iterator &key_it)
{
    std::vector<types::ArgumentList_t::const_iterator> values;
    auto value_it = std::next(key_it);

    for (auto it = value_it; it != g_args.end(); ++it)
    {
        auto found_key_it = std::find(g_keys.cbegin(), g_keys.cend(), it);

        if (found_key_it != g_keys.cend())
        {
            break;
        }

        values.emplace_back(it);
    }

    return values;
}


/**
 * @brief Find an argument key within #g_args.
 *
 * @param The argument key to look for.
 *
 * @return An argument container list iterator at the key position.
 */
static const types::ArgumentList_t::const_iterator find_key(const types::Key_t &key)
{
    auto key_it = std::find(g_args.cbegin(), g_args.cend(), key);

    if (key_it == g_args.cend())
    {
        std::ostringstream message;
        message << "Couldn't find argument '" << key << "'.";

        throw errors::ArgumentKeyError(message.str());
    }

    return key_it;
}


} // namespace cppargparse::algorithm

#endif // CPPARGPARSE_ALGORITHM_H
