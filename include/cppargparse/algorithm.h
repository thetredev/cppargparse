#ifndef CPPARGPARSE_ALGORITHM_H
#define CPPARGPARSE_ALGORITHM_H

#include <vector>

#include "globals.h"
#include "types.h"


namespace cppargparse::algorithm {


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


} // namespace cppargparse::algorithm

#endif // CPPARGPARSE_ALGORITHM_H
