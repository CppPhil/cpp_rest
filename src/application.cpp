#include "../include/application.hpp"
#include "../include/discover_black_board_service.hpp" // cr::discoverBlackBoardService
#include "../include/safe_optional_access.hpp" // cr::safeOptionalAccess
#include <ciso646> // not
#include <string> // std::getline
#include <iostream> // std::cout, std::cin
#include <utility> // std::move

namespace cr
{
Application::Application()
    : m_blackBoardRegistration{ boost::none },
      m_applicationState{ s_ostream, s_istream },
      m_consoleMenu{ s_ostream, s_istream },
      m_exitApplication{ makeConsoleMenuItem(
          ConsoleMenuItem::Identifier::ExitApplication,
          "Exit the application",
          [](ApplicationState &) { })
      },
      m_discoverBlackBoard{ makeConsoleMenuItem(
          ConsoleMenuItem::Identifier::DiscoverBlackBoard,
          "Discover the BlackBoard service",
          &discoverBlackBoardService)
      },
      m_registerUser{ makeConsoleMenuItem(
          ConsoleMenuItem::Identifier::RegisterUser,
          "Register a user with the BlackBoard service",
          [this](ApplicationState &) {
              BlackBoardRegistration &blackBoardRegistration{
                  safeOptionalAccess(m_blackBoardRegistration)
              };

              blackBoardRegistration.registerUser();
          })
      }
{
    setConsoleMenuToDefaultItems();
}

Application &Application::start()
{
    for (;;) {
        m_consoleMenu.sort(); // sort the menu items.

        const ConsoleMenuItem::Identifier lastRun{ m_consoleMenu.run() };

        switch (lastRun) {
        case ConsoleMenuItem::Identifier::DiscoverBlackBoard:
            m_consoleMenu.erase(ConsoleMenuItem::Identifier::DiscoverBlackBoard);
            m_consoleMenu.addItem(m_registerUser);
            if (not createBlackBoardRegistration()) {
                CR_THROW_WITH_SOURCE_INFO(
                    std::logic_error,
                    "BlackBoardRegistration could not be created!");
            }
            break;
        case ConsoleMenuItem::Identifier::None:
            // FALLTHROUGH
        case ConsoleMenuItem::Identifier::ExitApplication:
            goto exit;
        }
    }

exit:
    return *this;
}

std::ostream &Application::s_ostream = std::cout;
std::istream &Application::s_istream = std::cin;

ConsoleMenuItem Application::makeConsoleMenuItem(
    ConsoleMenuItem::Identifier identifier,
    std::string text,
    std::function<void (ApplicationState &)> action)
{
    return ConsoleMenuItem{
        identifier, m_applicationState, std::move(text), std::move(action)
    };
}

void Application::setConsoleMenuToDefaultItems()
{
    m_consoleMenu.clear();
    m_consoleMenu.addItem(m_discoverBlackBoard);
    m_consoleMenu.addItem(m_exitApplication);
}

bool Application::createBlackBoardRegistration()
{
    boost::optional<BlackBoardInfo> &optional{
        m_applicationState.blackBoardInfo
    };

    if (not optional) {
        return false;
    }

    BlackBoardInfo &blackBoardInfo{ *optional };

    m_blackBoardRegistration
        = BlackBoardRegistration{
            m_applicationState,
            blackBoardInfo.ipAddress,
            blackBoardInfo.port
    };

    return true;
}
} // namespace cr

