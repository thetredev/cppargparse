#ifndef CPPARGPARSE_TYPES_H
#define CPPARGPARSE_TYPES_H

#include <string>
#include <vector>


namespace cppargparse::types {


/**
 * @brief The key type.
 */
typedef std::string Key_t;

/**
 * @brief The argument list container type.
 */
typedef std::vector<std::string> ArgumentList_t;

/**
 * @brief They key list type.
 */
typedef std::vector<ArgumentList_t::const_iterator> ArgumentKeyList_t;


} // namespace cppargparse::types

#endif // CPPARGPARSE_TYPES_H
