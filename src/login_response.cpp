#include "../include/login_response.hpp"
#include "../include/json.hpp" // cr::fetchString, cr::fetchDouble
#include <ciso646> // not
#include <utility> // std::move

namespace cr
{
LoginResponse LoginResponse::fromJson(const json::Document &jsonDocument)
{
    if (not jsonDocument.IsObject()) { // It must be a JSON object.
        CR_THROW_WITH_SOURCE_INFO(
            InvalidJsonException,
            "jsonDocument was not a JSON object.");
    }

    const std::string message{ fetchString(s_messageField, jsonDocument) };
    const std::string token{ fetchString(s_tokenField, jsonDocument) };
    const double validTill{ fetchDouble(s_validTillField, jsonDocument) };

    return { message, token, validTill };
}

LoginResponse::LoginResponse(
    std::string message,
    std::string token,
    double validTill)
    : m_message{ std::move(message) },
      m_token{ std::move(token) },
      m_validTill{ validTill }
{
}

boost::string_ref LoginResponse::getMessage() const noexcept
{
    return m_message;
}

boost::string_ref LoginResponse::getToken() const noexcept
{
    return m_token;
}

double LoginResponse::getValidTill() const noexcept
{
    return m_validTill;
}

const char LoginResponse::s_messageField[]   = "message";
const char LoginResponse::s_tokenField[]     = "token";
const char LoginResponse::s_validTillField[] = "valid_till";
} // namespace cr
