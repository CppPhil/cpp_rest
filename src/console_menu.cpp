#include "../include/console_menu.hpp"
#include "../include/safe_optional_access.hpp" // cr::safeOptionalAccess
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <boost/algorithm/string/trim.hpp> // boost::trim
#include <ciso646> // and, not
#include <string> // std::string, std::getline
#include <utility> // std::move
#include <iomanip> // std::setw
#include <limits> // std::numeric_limits

namespace cr
{
ConsoleMenu::ConsoleMenu(std::ostream &ostream, std::istream &istream)
    : m_menuItems{ },
      m_ostream{ &ostream },
      m_istream{ &istream }
{
}

ConsoleMenu &ConsoleMenu::addItem(const ConsoleMenuItem &menuItem)
{
    m_menuItems.push_back(menuItem);
    return *this;
}

ConsoleMenu &ConsoleMenu::addItem(ConsoleMenuItem &&menuItem) noexcept
{
    m_menuItems.push_back(std::move(menuItem));
    return *this;
}

ConsoleMenu &ConsoleMenu::clear()
{
    m_menuItems.clear();
    return *this;
}

ConsoleMenu::container_type::size_type ConsoleMenu::size() const noexcept
{
    return m_menuItems.size();
}

ConsoleMenu &ConsoleMenu::erase(ConsoleMenuItem::Identifier identifier)
{
    return eraseIf([identifier](const ConsoleMenuItem &item) {
        return item.getIdentifier() == identifier;
    });
}

ConsoleMenuItem::Identifier ConsoleMenu::run()
{
    std::ostream &ostream{ *m_ostream };
    std::istream &istream{ *m_istream };

    ostream << "\nOptions:\n";

    if (m_menuItems.empty()) {
        ostream << "There is nothing to do.\n";
        return ConsoleMenuItem::Identifier::None;
    }

    displayItems(ostream);

    boost::optional<std::size_t> opt{ boost::none };

    for (bool firstTry{ true }; not opt; firstTry = false) {
        if (firstTry) {
            displayPrompt(ostream);
        } else {
            ostream << "Try again: " << std::flush;
        }

        opt = readInput(istream);
    }

    const std::size_t index{ safeOptionalAccess(opt) - s_offset };
    runByIndex(index);

    ostream << '\n';
    return m_menuItems.at(index).getIdentifier();
}

const std::size_t ConsoleMenu::s_offset = 1U;

const int ConsoleMenu::s_idxWidth = 3;

const int ConsoleMenu::s_defaultWidth = 0;

const char ConsoleMenu::s_promptText[] = "Enter the desired option: ";

void ConsoleMenu::displayItems(std::ostream &ostream)
{
    for (std::size_t i{ }; i < m_menuItems.size(); ++i) {
        ostream << std::setw(s_idxWidth) << (i + s_offset);
        ostream.width(s_defaultWidth);
        ostream << ": ";
        m_menuItems.at(i).display(ostream);
        ostream << '\n';
    }
}

void ConsoleMenu::displayPrompt(std::ostream &ostream)
{
    ostream << '\n' << s_promptText << std::flush;
}

boost::optional<std::size_t> ConsoleMenu::readInput(std::istream &istream)
{
    std::string lineRead{ };

    std::getline(istream, lineRead);

    boost::trim(lineRead);

    if (istream and isInputValid(lineRead)) {
        return boost::make_optional(boost::lexical_cast<std::size_t>(lineRead));
    }

    istream.clear();
    return boost::none;
}

bool ConsoleMenu::isInputValid(std::string &inputLine)
{
    std::size_t value{ std::numeric_limits<std::size_t>::max() };

    try {
        value = boost::lexical_cast<std::size_t>(inputLine);
    } catch (const boost::bad_lexical_cast &) {
        return false;
    }

    return (value - s_offset) < size();
}

void ConsoleMenu::runByIndex(std::size_t idx)
{
    m_menuItems.at(idx).runAction();
}
} // namespace cr
