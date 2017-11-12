#include "../include/namespace_aliases.hpp"
#include "../include/black_board_registration.hpp"
#include "../include/request.hpp" // cr::sendRequestSync
#include "../include/response.hpp" // cr::getContentLength
#include "../include/json.hpp" // cr::asJson
#include "../include/get_none_empty_line.hpp" // cr::getNoneEmptyLine
#include <corvusoft/restbed/settings.hpp> // restbed::Settings
#include <corvusoft/restbed/http.hpp> // restbed::Http::fetch
#include <cstddef> // std::size_t
#include <utility> // std::move

#include "../include/log.hpp"

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

    CR_LOG(LogLevel::debug) << "Got userName: " << userName << "\n"
                            << "and passWord: " << passWord;

    m_appState->blackBoardRegistrationInfo = BlackBoardRegistrationInfo{
        userName, passWord
    };

    CR_LOG(LogLevel::debug) << "replaced BlackBoardRegistrationInfo";

    const RegisterUserType registerUserType = { userName, passWord };

    CR_LOG(LogLevel::debug) << "created registerUserType";

    json::Document jsonDocument{ asJson(registerUserType) };

    CR_LOG(LogLevel::debug) << "converted registerUserType to JSON";

    std::shared_ptr<rest::Response> responsePtr{ sendRequestSync(
        m_blackBoardIpAddress,
        m_port,
        verb,
        pathToResource,
        jsonDocument)
    };

    CR_LOG(LogLevel::debug) << "send synchronous request";

    CR_THROW_IF_NULL(responsePtr);

    CR_LOG(LogLevel::debug) << "responsePtr was not nullptr";

    rest::Response &response{ *responsePtr };
    const std::size_t contentLength{ getContentLength(response) };

    CR_LOG(LogLevel::debug) << "got contentLength: " << contentLength;

    rest::Http::fetch(contentLength, responsePtr);

    CR_LOG(LogLevel::debug) << "fetched bytes";

    const rest::Bytes body{ response.get_body() };

    CR_LOG(LogLevel::debug) << "got body";

    // TODO: here
    m_appState->ostream->write(
        reinterpret_cast<const char *>(body.data()),
        static_cast<std::streamsize>(body.size()));

    CR_LOG(LogLevel::debug) << "wrote body to ostream";

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
