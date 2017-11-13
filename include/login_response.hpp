#ifndef INCG_CR_LOGIN_RESPONSE_HPP
#define INCG_CR_LOGIN_RESPONSE_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/except.hpp" // cr::InvalidJsonException
#include <rapidjson/document.h> // rapidjson::Document
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <string> // std::string

namespace cr
{
class LoginResponse
{
public:
    using this_type = LoginResponse;

    static LoginResponse fromJson(const json::Document &jsonDocument);

    LoginResponse(std::string message, std::string token, double validTill);

    boost::string_ref getMessage() const noexcept;

    boost::string_ref getToken() const noexcept;

    double getValidTill() const noexcept;

private:
    static const char s_messageField[];
    static const char s_tokenField[];
    static const char s_validTillField[];

    std::string m_message;
    std::string m_token;
    double m_validTill;
};
} // namespace cr
#endif // INCG_CR_LOGIN_RESPONSE_HPP
