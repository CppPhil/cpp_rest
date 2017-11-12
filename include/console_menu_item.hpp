#ifndef INCG_CR_CONSOLE_MENU_ITEM_HPP
#define INCG_CR_CONSOLE_MENU_ITEM_HPP
#include "../include/application_state.hpp" // cr::ApplicationState
#include <gsl/gsl> // gsl::not_null
#include <iosfwd> // std::ostream
#include <string> // std::string
#include <functional> // std::function

namespace cr
{
class ConsoleMenuItem
{
public:
    using this_type = ConsoleMenuItem;

    enum class Identifier
    {
        None,
        ExitApplication,
        DiscoverBlackBoard
    };

    ConsoleMenuItem(
        Identifier identifier,
        ApplicationState &applicationState,
        std::string text,
        std::function<void (ApplicationState &)> action);

    this_type &display(std::ostream &ostream);

    this_type &runAction();

    Identifier getIdentifier() const noexcept;

private:
    Identifier m_identifier;
    gsl::not_null<ApplicationState *> m_applicationState;
    std::string m_text;
    std::function<void (ApplicationState &)> m_action;
};
} // namespace cr
#endif // INCG_CR_CONSOLE_MENU_ITEM_HPP
