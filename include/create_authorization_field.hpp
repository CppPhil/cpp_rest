#ifndef INCG_CR_CREATE_AUTHORIZATION_FIELD_HPP
#define INCG_CR_CREATE_AUTHORIZATION_FIELD_HPP
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <string> // std::string

namespace cr
{
std::string createAuthorizationField(
    boost::string_ref userName,
    boost::string_ref passWord);
} // namespace cr
#endif // INCG_CR_CREATE_AUTHORIZATION_FIELD_HPP
