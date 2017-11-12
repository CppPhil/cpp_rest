#include "../include/application.hpp"
#include "../include/discover_black_board_service.hpp" // cr::discoverBlackBoardService
#include <iostream> // std::cout, std::cin
#include <utility> // std::move

namespace cr
{
Application::Application()
    : m_applicationState{ s_ostream, s_istream },
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
      }
{
    setConsoleMenuToDefaultItems();
}

Application &Application::start()
{
    for (;;) {
        const ConsoleMenuItem::Identifier lastRun{ m_consoleMenu.run() };

        switch (lastRun) {
        case ConsoleMenuItem::Identifier::None:
            // FALLTHROUGH
        case ConsoleMenuItem::Identifier::ExitApplication:
            return *this;
        }
    }

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
} // namespace cr

