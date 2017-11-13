#include "../include/console_menu.hpp"
#include "../include/safe_optional_access.hpp" // cr::safeOptionalAccess
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <boost/algorithm/string/trim.hpp> // boost::trim
#include <ciso646> // and, not
#include <string> // std::string, std::getline
#include <utility> // std::move
#include <iomanip> // std::setw
#include <limits> // std::numeric_limits
#include <iterator> // std::begin, std::end
#include <type_traits> // std::underlying_type_t

namespace cr
{
ConsoleMenu::value_type::value_type(ConsoleMenuItem p_menuItem)
    : menuItem{ std::move(p_menuItem) },
      wasActionExecutedSuccessfully{ false } // default to false, since the
                                             // action has not been run by
                                             // default.
{
}

ConsoleMenu::ConsoleMenu(std::ostream &ostream, std::istream &istream)
    : m_cont{ },
      m_ostream{ &ostream },
      m_istream{ &istream }
{
}

ConsoleMenu &ConsoleMenu::addItem(const ConsoleMenuItem &menuItem)
{
    m_cont.emplace_back(menuItem);
    return *this;
}

ConsoleMenu &ConsoleMenu::addItem(ConsoleMenuItem &&menuItem) noexcept
{
    m_cont.emplace_back(std::move(menuItem));
    return *this;
}

ConsoleMenu &ConsoleMenu::clear()
{
    m_cont.clear();
    return *this;
}

ConsoleMenu::container_type::size_type ConsoleMenu::size() const noexcept
{
    return m_cont.size();
}

ConsoleMenu &ConsoleMenu::erase(ConsoleMenuItem::Identifier identifier)
{
    return eraseIf([identifier](const value_type &elem) {
        return elem.menuItem.getIdentifier() == identifier;
    });
}

ConsoleMenuItem::Identifier ConsoleMenu::run()
{
    std::ostream &ostream{ *m_ostream };
    std::istream &istream{ *m_istream };

    ostream << "\nOptions:\n";

    if (m_cont.empty()) {
        ostream << "There is nothing to do.\n";
        return ConsoleMenuItem::Identifier::None;
    }

    displayItems(ostream);

    boost::optional<std::size_t> opt{ boost::none };

    // keep trying again until a value that was valid is entered.
    for (bool firstTry{ true }; not opt; firstTry = false) {
        if (firstTry) {
            displayPrompt(ostream);
        } else {
            ostream << "Try again: " << std::flush;
        }

        opt = readInput(istream);
    }

    const std::size_t index{ safeOptionalAccess(opt) - s_offset };
    m_cont.at(index).wasActionExecutedSuccessfully = runByIndex(index);

    ostream << '\n';
    return m_cont.at(index).menuItem.getIdentifier();
}

ConsoleMenu &ConsoleMenu::sort()
{
    std::sort(
        std::begin(m_cont),
        std::end(m_cont),
        [](const value_type &lhs, const value_type &rhs) {
            using Underlying
                = std::underlying_type_t<ConsoleMenuItem::Identifier>;

            return static_cast<Underlying>(lhs.menuItem.getIdentifier())
                > static_cast<Underlying>(rhs.menuItem.getIdentifier());
    });

    return *this;
}

const ConsoleMenuItem *ConsoleMenu::findByIdentifier(
    ConsoleMenuItem::Identifier identifier) const noexcept
{
    const container_type::const_iterator it{
        findByIdentifierHelper(identifier)
    };

    return ((it == std::end(m_cont)) ? (nullptr) : (&(it->menuItem)));
}

bool ConsoleMenu::getExecutionStatus(
    ConsoleMenuItem::Identifier identifier) const noexcept
{
    const container_type::const_iterator it{
        findByIdentifierHelper(identifier)
    };

    return ((it == std::end(m_cont))
            ? (false) : (it->wasActionExecutedSuccessfully));
}

const std::size_t ConsoleMenu::s_offset = 1U;

const int ConsoleMenu::s_idxWidth = 3; /* hopefully there won't be more than 999 menu items */

const int ConsoleMenu::s_defaultWidth = 0;

const char ConsoleMenu::s_promptText[] = "Enter the desired option: ";

void ConsoleMenu::displayItems(std::ostream &ostream)
{
    for (std::size_t i{ }; i < m_cont.size(); ++i) {
        ostream << std::setw(s_idxWidth) << (i + s_offset);
        ostream.width(s_defaultWidth);
        ostream << ": ";
        m_cont.at(i).menuItem.display(ostream);
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

    boost::trim(lineRead); // get rid of superfluous whitespace at the front and back.

    // if the istream is still ok and the input is valid -> good.
    if (istream and isInputValid(lineRead)) {
        return boost::make_optional(boost::lexical_cast<std::size_t>(lineRead));
    }

    // otherwise, an error occurred.
    istream.clear(); // clear the istream error flags, so that it works again.
    return boost::none; // return an optional indicating failure to read.
}

bool ConsoleMenu::isInputValid(const std::string &inputLine)
{
    // some garbage dummy value.
    std::size_t value{ std::numeric_limits<std::size_t>::max() };

    try {
        // replace the value with the value extracted from 'inputLine'.
        value = boost::lexical_cast<std::size_t>(inputLine);
    } catch (const boost::bad_lexical_cast &) {
        // if lexical_cast failed -> the input is invalid.
        return false;
    }

    // lexical_cast succeeded.
    // check if the value extracted is within the allowable bounds.
    return (value - s_offset) < size();
}

bool ConsoleMenu::runByIndex(std::size_t idx) /* note: zero based index here. */
{
    return m_cont.at(idx).menuItem.runAction();
}

ConsoleMenu::container_type::const_iterator ConsoleMenu::findByIdentifierHelper(
    ConsoleMenuItem::Identifier identifier) const noexcept
{
    return std::find_if(
        std::begin(m_cont), std::end(m_cont),
        [identifier](const value_type &elem) {
            return elem.menuItem.getIdentifier() == identifier;
        });
}
} // namespace cr
