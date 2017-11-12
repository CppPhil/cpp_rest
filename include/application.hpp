#ifndef INCG_CR_APPLICATION_HPP
#define INCG_CR_APPLICATION_HPP
#include "../include/noncopyable.hpp" // CR_NONCOPYABLE
#include "../include/application_state.hpp" // cr::ApplicationState
#include "../include/console_menu.hpp" // cr::ConsoleMenu
#include "../include/console_menu_item.hpp" // cr::ConsoleMenuItem
#include <ostream> // std::ostream
#include <istream> // std::istream

namespace cr
{
class Application
{
public:
    using this_type = Application;

    CR_NONCOPYABLE(Application);

    Application();

    this_type &start();

private:
    static std::ostream &s_ostream;
    static std::istream &s_istream;

    ConsoleMenuItem makeConsoleMenuItem(
        ConsoleMenuItem::Identifier identifier,
        std::string text,
        std::function<void (ApplicationState &)> action);

    ApplicationState m_applicationState;
    ConsoleMenu m_consoleMenu;
    const ConsoleMenuItem m_exitApplication;
    const ConsoleMenuItem m_discoverBlackBoard;
};
} // namespace cr
#endif // INCG_CR_APPLICATION_HPP
