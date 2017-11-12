#include "../include/console_menu_item.hpp"
#include "../include/invoke.hpp" // cr::invoke
#include <utility> // std::move

namespace cr
{
ConsoleMenuItem::ConsoleMenuItem(
    Identifier identifier,
    ApplicationState &applicationState,
    std::string text,
    std::function<void (ApplicationState &)> action)
    : m_identifier{ identifier },
      m_applicationState{ &applicationState },
      m_text{ std::move(text) },
      m_action{ std::move(action) }
{
}

ConsoleMenuItem &ConsoleMenuItem::display(std::ostream &ostream)
{
    ostream << m_text;
    return *this;
}

ConsoleMenuItem &ConsoleMenuItem::runAction()
{
    ::cr::invoke(m_action, *m_applicationState);
    return *this;
}

ConsoleMenuItem::Identifier ConsoleMenuItem::getIdentifier() const noexcept
{
    return m_identifier;
}
} // namespace cr
