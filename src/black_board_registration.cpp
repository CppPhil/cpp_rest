#include "../include/namespace_aliases.hpp"
#include "../include/black_board_registration.hpp"
#include "../include/request.hpp" // cr::sendRequestSync
#include "../include/response.hpp" // cr::getContentLength
#include "../include/json.hpp" // cr::asJson
#include "../include/get_none_empty_line.hpp" // cr::getNoneEmptyLine
#include "../include/http_status_code.hpp" // cr::HttpStatusCode
#include <corvusoft/restbed/http.hpp> // rest::Http::fetch
#include <corvusoft/restbed/settings.hpp> // restbed::Settings
#include <corvusoft/restbed/response.hpp> // restbed::Response
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

BlackBoardRegistration &BlackBoardRegistration::registerUser()
{
    static constexpr HttpVerb verb = HttpVerb::POST;
    static constexpr char pathToResource[] = "/users";

    const std::string userName{ getUserNameFromUser() };
    const std::string passWord{ getPassWordFromUser() };

    m_appState->blackBoardRegistrationInfo = BlackBoardRegistrationInfo{
        userName, passWord
    };

    const RegisterUserType registerUserType = { userName, passWord };

    json::Document jsonDocument{ asJson(registerUserType) };

    std::shared_ptr<rest::Response> responsePtr{ sendRequestSync(
        m_blackBoardIpAddress,
        m_port,
        verb,
        pathToResource,
        jsonDocument)
    };

    CR_THROW_IF_NULL(responsePtr);

    std::ostream &ostream{ *(m_appState->ostream) };

    ostream
        << "\nGot status code: "
        << static_cast<HttpStatusCode>(responsePtr->get_status_code())
        << '\n';

    const rest::Bytes bytes{ rest::Http::to_bytes(responsePtr) };

    ostream << "bytes: ";
    ostream.write(
        reinterpret_cast<const char *>(bytes.data()),
        static_cast<std::streamsize>(bytes.size()));
    ostream << '\n';

    return *this;
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
} // namespace cr
