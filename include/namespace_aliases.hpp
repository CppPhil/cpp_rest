/*!
 * \file namespace_aliases.hpp
 * \brief Defines shorthand aliases for namespace restbed and
 *        namespace rapidjson in namespace cr.
**/
#ifndef INCG_CR_NAMESPACE_ALIASES_HPP
#define INCG_CR_NAMESPACE_ALIASES_HPP

namespace restbed
{
} // namespace restbed

namespace rapidjson
{
} // namespace rapidjson

namespace cr
{
namespace rest = ::restbed;
namespace json = ::rapidjson;
} // namespace cr
#endif // INCG_CR_NAMESPACE_ALIASES_HPP
