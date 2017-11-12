#ifndef INCG_CR_BLACK_BOARD_REGISTRATION_HPP
#define INCG_CR_BLACK_BOARD_REGISTRATION_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/application_state.hpp" // cr::ApplicationState
#include "../include/except.hpp" // CR_THROW_IF_NULL
#include <rapidjson/stringbuffer.h> // rapidjson::StringBuffer
#include <rapidjson/prettywriter.h> // rapidjson::PrettyWriter
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <gsl/gsl> // gsl::not_null
#include <cstdint> // std::uint16_t
#include <string> // std::string

namespace cr
{
class BlackBoardRegistration
{
public:
    using this_type = BlackBoardRegistration;

    struct RegisterUserType
    {
        void asJson(
            json::PrettyWriter<json::StringBuffer> &writer) const noexcept;

        boost::string_ref userName;
        boost::string_ref passWord;
    };

    BlackBoardRegistration(
        ApplicationState &appState,
        std::string blackBoardIpAddress,
        std::uint16_t port);

    this_type &registerUser();

private:
    std::string getUserNameFromUser();

    std::string getPassWordFromUser();

    gsl::not_null<ApplicationState *> m_appState;
    std::string m_blackBoardIpAddress;
    std::uint16_t m_port;
};
} // namespace cr
#endif // INCG_CR_BLACK_BOARD_REGISTRATION_HPP