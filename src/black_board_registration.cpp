#include "../include/namespace_aliases.hpp"
#include "../include/black_board_registration.hpp"
#include "../include/request.hpp" // cr::sendRequestSync
#include "../include/response.hpp" // cr::getContentLength
#include "../include/json.hpp" // cr::asJson
#include "../include/get_none_empty_line.hpp" // cr::getNoneEmptyLine
#include "../include/http_status_code.hpp" // cr::HttpStatusCode
#include "../include/create_authorization_field.hpp" // cr::createAuthorizationField
#include "../include/safe_optional_access.hpp" // cr::safeOptionalAccess
#include <corvusoft/restbed/http.hpp> // rest::Http::fetch
#include <corvusoft/restbed/settings.hpp> // restbed::Settings
#include <corvusoft/restbed/response.hpp> // restbed::Response
#include <boost/current_function.hpp> // BOOST_CURRENT_FUNCTION
#include <ciso646> // not
#include <cstddef> // std::size_t
#include <iterator> // std::begin, std::end
#include <string> // std::string
#include <utility> // std::move

namespace cr
{
void BlackBoardRegistration::RegisterUserType::asJson(
    json::PrettyWriter<json::StringBuffer> &writer) const noexcept
{
    static constexpr char firstField[]  = "name";
    static constexpr char secondField[] = "password";

    writer.StartObject();

    writer.String(firstField);
    writer.String(userName.data());

    writer.String(secondField);
    writer.String(passWord.data());

    writer.EndObject();
}

BlackBoardRegistration::BlackBoardRegistration(
    ApplicationState &appState,
    std::string blackBoardIpAddress,
    std::uint16_t port)
    : m_appState{ &appState },
      m_blackBoardIpAddress{ std::move(blackBoardIpAddress) },
      m_port{ port }
{
}

bool BlackBoardRegistration::registerUser()
{
    static constexpr HttpVerb verb                     = HttpVerb::POST;
    static constexpr char pathToResource[]             = "/users";
    static constexpr HttpStatusCode expectedStatusCode = HttpStatusCode::CREATED;

    const std::string userName{ getUserNameFromUser() };
    const std::string passWord{ getPassWordFromUser() };

    m_appState->blackBoardRegistrationInfo = BlackBoardRegistrationInfo{
        userName, passWord
    };

    const json::Document jsonDocument{ createJsonUserNamePw(userName, passWord) };

    std::shared_ptr<rest::Request> requestPtr{ nullptr };
    std::shared_ptr<rest::Response> responsePtr{ sendToBlackBoardSync(
        requestPtr,
        verb,
        pathToResource,
        jsonDocument)
    };

    CR_THROW_IF_NULL(responsePtr);

    std::ostream &ostream{ *(m_appState->ostream) };

    const HttpStatusCode statusCode{
        static_cast<HttpStatusCode>(responsePtr->get_status_code()) };

    ostream << "\nGot status code: " << statusCode << '\n';

    const std::size_t contentLength{ getContentLength(*responsePtr) };
    rest::Http::fetch(contentLength, responsePtr);
    const rest::Bytes bodyAsBytes{ responsePtr->get_body() };
    ostream << "body:\n";
    ostream.write(
        reinterpret_cast<const char *>(bodyAsBytes.data()),
        static_cast<std::streamsize>(bodyAsBytes.size()));
    ostream << '\n';

    return statusCode == expectedStatusCode;
}

bool BlackBoardRegistration::login()
{
    static constexpr HttpVerb verb         = HttpVerb::GET;
    static constexpr char pathToResource[] = "/login";
    static constexpr HttpStatusCode expectedStatuscode = HttpStatusCode::OK;

    const BlackBoardRegistrationInfo &blackBoardRegistrationInfo{
        safeOptionalAccess(m_appState->blackBoardRegistrationInfo)
    };

    const json::Document jsonDocument{ createJsonUserNamePw(
        blackBoardRegistrationInfo.userName,
        blackBoardRegistrationInfo.passWord)
    };

    const std::multimap<std::string, std::string> headers{
        { "Authorization",
          cr::createAuthorizationField(
              blackBoardRegistrationInfo.userName,
              blackBoardRegistrationInfo.passWord) }
    };

    std::shared_ptr<rest::Request> requestPtr{ nullptr };
    std::shared_ptr<rest::Response> responsePtr{ sendToBlackBoardSync(
        requestPtr,
        verb,
        pathToResource,
        jsonDocument,
        headers)
    };

    CR_THROW_IF_NULL(responsePtr);

    std::ostream &ostream{ *(m_appState->ostream) };

    const HttpStatusCode statusCode{
        static_cast<HttpStatusCode>(responsePtr->get_status_code())
    };

    ostream << "\nGot status code: " << statusCode << '\n';

    const std::size_t length{
        getContentLength(*responsePtr)
    };

    // Fetch the response body.
    cr::rest::Http::fetch(length, responsePtr);

    const rest::Bytes bodyBytes{ responsePtr->get_body() };
    const std::string body(std::begin(bodyBytes), std::end(bodyBytes));
    ostream << "body:\n" << body << '\n';

    if (statusCode == expectedStatuscode) {
        m_appState->loginResponse = LoginResponse::fromJson(parseJson(body));
        return true;
    }

    return false;
}

bool BlackBoardRegistration::whoami()
{
    static constexpr HttpVerb verb         = HttpVerb::GET;
    static constexpr char pathToResource[] = "/whoami";

    std::ostream &ostream{ *(m_appState->ostream) };

    if (not m_appState->loginResponse) {
        ostream << BOOST_CURRENT_FUNCTION << ": appState had no loginResponse!\n";
        return false;
    }

    const LoginResponse &loginResponse{ *(m_appState->loginResponse) };
    const std::string token{ loginResponse.getToken() };

    const std::multimap<std::string, std::string> headers{
        { "Authorization", "Token " + token }
    };

    const json::Document emptyJsonDocument{ parseJson("{}") };

    std::shared_ptr<rest::Request> requestPtr{ nullptr };
    std::shared_ptr<rest::Response> responsePtr{ sendToBlackBoardSync(
        requestPtr,
        verb,
        pathToResource,
        emptyJsonDocument,
        headers)
    };

    CR_THROW_IF_NULL(responsePtr);

    const HttpStatusCode httpStatusCode{
        static_cast<HttpStatusCode>(responsePtr->get_status_code())
    };

    ostream << "statusCode: " << httpStatusCode << '\n';

    const std::size_t contentLength{ getContentLength(*responsePtr) };

    rest::Http::fetch(contentLength, responsePtr);

    const rest::Bytes bodyBytes{ responsePtr->get_body() };
    const std::string body(std::begin(bodyBytes), std::end(bodyBytes));
    ostream << "body:\n" << body << '\n';

    return true;
}

std::string BlackBoardRegistration::getUserNameFromUser()
{
    static constexpr char prompt[] = "Enter your user name:";

    std::string userName{ };

    getNoneEmptyLine(
        *(m_appState->istream),
        userName,
        *(m_appState->ostream),
        prompt);

    return userName;
}

std::string BlackBoardRegistration::getPassWordFromUser()
{
    static constexpr char prompt[] = "Enter your password:";

    std::string passWord{ };

    getNoneEmptyLine(
        *(m_appState->istream),
        passWord,
        *(m_appState->ostream),
        prompt);

    return passWord;
}

json::Document BlackBoardRegistration::createJsonUserNamePw(
    boost::string_ref userName,
    boost::string_ref passWord) const
{
    const RegisterUserType registerUserType = { userName, passWord };
    return asJson(registerUserType);
}

std::shared_ptr<rest::Response> BlackBoardRegistration::sendToBlackBoardSync(
    std::shared_ptr<rest::Request> &requestOutParam,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    const json::Document &jsonDocument,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    return sendRequestSync(
        requestOutParam,
        m_blackBoardIpAddress,
        m_port,
        httpVerb,
        pathToResource,
        jsonDocument,
        headers,
        queryParameters);
}
} // namespace cr
