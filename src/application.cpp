#include "../include/application.hpp"
#include "../include/discover_black_board_service.hpp" // cr::discoverBlackBoardService
#include "../include/safe_optional_access.hpp" // cr::safeOptionalAccess
#include <ciso646> // not
#include <string> // std::getline
#include <iostream> // std::cout, std::cin
#include <utility> // std::move
#include <iterator> // std::begin, std::end

namespace cr
{
Application::Application()
    : m_restClient{ boost::none },
      m_applicationState{ s_ostream, s_istream },
      m_consoleMenu{ s_ostream, s_istream },
      m_exitApplication{ makeConsoleMenuItem(
          ConsoleMenuItem::Identifier::ExitApplication,
          "Exit the application",
          [](ApplicationState &) {
              s_ostream << "\nExiting application.\n";
              return true; // always succeeds.
          })
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
              RestClient &blackBoardRegistration{
                  safeOptionalAccess(m_restClient)
              };

              return blackBoardRegistration.registerUser();
          })
      },
      m_login{ makeConsoleMenuItem(
          ConsoleMenuItem::Identifier::Login,
          "Login to the BlackBoard",
          [this](ApplicationState &) {
              RestClient &blackBoardRegistration{
                  safeOptionalAccess(m_restClient)
              };

              return blackBoardRegistration.login();
          })
      },
      m_whoami{ makeConsoleMenuItem(
          ConsoleMenuItem::Identifier::WhoAmI,
          "Check the login with the BlackBoard using WhoAmI",
          [this](ApplicationState &) {
              return safeOptionalAccess(m_restClient).whoami();
          })
      },
      m_fetchPublicQuests{ makeConsoleMenuItem(
          ConsoleMenuItem::Identifier::FetchPublicQuests,
          "Fetch the available public quests",
          [this](ApplicationState &) {
              return safeOptionalAccess(m_restClient).fetchPublicQuests();
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
        case ConsoleMenuItem::Identifier::RegisterUser:
            // if the action was executed successfully
            // -> replace the menu item with the next one.
            if (m_consoleMenu.getExecutionStatus(
                    ConsoleMenuItem::Identifier::RegisterUser)) {
                m_consoleMenu.erase(ConsoleMenuItem::Identifier::RegisterUser);
                m_consoleMenu.addItem(m_login);
            }
            // otherwise -> do nothing (repeat the menu item to register a user)

            break;
        case ConsoleMenuItem::Identifier::Login:
            if (m_consoleMenu.getExecutionStatus(
                    ConsoleMenuItem::Identifier::Login)) {
                m_consoleMenu.erase(ConsoleMenuItem::Identifier::Login);
                m_consoleMenu.addItem(m_whoami);
            }
            break;
        case ConsoleMenuItem::Identifier::WhoAmI:
            if (m_consoleMenu.getExecutionStatus(
                    ConsoleMenuItem::Identifier::WhoAmI)) {
                m_consoleMenu.erase(ConsoleMenuItem::Identifier::WhoAmI);
                m_consoleMenu.addItem(m_fetchPublicQuests);
            }
            break;
        case ConsoleMenuItem::Identifier::FetchPublicQuests:
            if (m_consoleMenu.getExecutionStatus(
                    ConsoleMenuItem::Identifier::FetchPublicQuests)) {
                for (const Quest &quest : m_applicationState.quests) {
                    using namespace std::literals::string_literals;

                    m_consoleMenu.addItem(makeConsoleMenuItem(
                        ConsoleMenuItem::Identifier::Quest,
                        "Attend quest \""s + quest.getName().data() + "\""s,
                        [this, &quest](ApplicationState &) {
                            return safeOptionalAccess(m_restClient)
                                .attendQuest(quest);
                        }));
                }
            }
            break;
        case ConsoleMenuItem::Identifier::Quest: {
            const ConsoleMenu::value_type &lastExecuted{
                m_consoleMenu.getLastExecuted()
            };

            if (lastExecuted.wasActionExecutedSuccessfully) {
                m_consoleMenu.eraseIf(
                    [&lastExecuted](const ConsoleMenu::value_type &elem) {
                        return elem.menuItem.getText()
                            == lastExecuted.menuItem.getText();
                });
            }

            break;
        }
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
    std::function<bool (ApplicationState &)> action)
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

    m_restClient
        = RestClient{
            m_applicationState,
            blackBoardInfo.ipAddress,
            blackBoardInfo.portFromMessage
    };

    return true;
}
} // namespace cr

