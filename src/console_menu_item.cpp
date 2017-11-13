#include "../include/console_menu_item.hpp"
#include "../include/invoke.hpp" // cr::invoke
#include <ciso646> // and, not
#include <utility> // std::move

namespace cr
{
ConsoleMenuItem::ConsoleMenuItem(
    Identifier identifier,
    ApplicationState &applicationState,
    std::string text,
    std::function<bool (ApplicationState &)> action)
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

bool ConsoleMenuItem::runAction()
{
    return ::cr::invoke(m_action, *m_applicationState);
}

ConsoleMenuItem::Identifier ConsoleMenuItem::getIdentifier() const noexcept
{
    return m_identifier;
}

const std::string &ConsoleMenuItem::getText() const noexcept
{
    return m_text;
}
} // namespace cr
