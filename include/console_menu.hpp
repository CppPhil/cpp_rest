#ifndef INCG_CR_CONSOLE_MENU_HPP
#define INCG_CR_CONSOLE_MENU_HPP
#include "../include/console_menu_item.hpp" // cr::ConsoleMenuItem
#include "../include/invoke.hpp" // cr::invoke
#include <boost/optional.hpp> // boost::optional
#include <gsl/gsl> // gsl::not_null
#include <cstddef> // std::size_t
#include <ostream> // std::ostream
#include <istream> // std::istream
#include <iterator> // std::back_inserter, std::iterator_traits, std::begin, std::end
#include <string> // std::string
#include <vector> // std::vector
#include <type_traits> // std::is_same
#include <algorithm> // std::copy, std::remove_if

namespace cr
{
class ConsoleMenu
{
public:
    using this_type = ConsoleMenu;
    using value_type = ConsoleMenuItem;
    using container_type = std::vector<value_type>;

    ConsoleMenu(std::ostream &ostream, std::istream &istream);

    this_type &addItem(const ConsoleMenuItem &menuItem);

    this_type &addItem(ConsoleMenuItem &&menuItem) noexcept;

    template <typename InputIterator>
    this_type &addItems(InputIterator first, InputIterator last)
    {
        static_assert(std::is_same<
            typename std::iterator_traits<InputIterator>::value_type,
            value_type>::value, "Invalid iterator type in ConsoleMenu::addItems.");
        std::copy(first, last, std::back_inserter(m_menuItems));
        return *this;
    }

    this_type &clear();

    container_type::size_type size() const noexcept;

    template <typename InputIterator>
    this_type &replaceItems(InputIterator first, InputIterator last)
    {
        clear();
        return addItems(first, last);
    }

    this_type &erase(ConsoleMenuItem::Identifier identifier);

    template <typename UnaryPredicate>
    this_type &eraseIf(UnaryPredicate unaryPredicate)
    {
        m_menuItems.erase(
            std::remove_if(
                std::begin(m_menuItems),
                std::end(m_menuItems),
                [&unaryPredicate](const ConsoleMenuItem &item) {
                    return ::cr::invoke(unaryPredicate, item);
                }),
            std::end(m_menuItems));
        return *this;
    }

    ConsoleMenuItem::Identifier run();

private:
    static const std::size_t s_offset;

    static const int s_idxWidth;

    static const int s_defaultWidth;

    static const char s_promptText[];

    void displayItems(std::ostream &ostream);

    void displayPrompt(std::ostream &ostream);

    boost::optional<std::size_t> readInput(std::istream &istream);

    bool isInputValid(std::string &inputLine);

    void runByIndex(std::size_t idx);

    container_type m_menuItems;
    gsl::not_null<std::ostream *> m_ostream;
    gsl::not_null<std::istream *> m_istream;
};
} // namespace cr
#endif // INCG_CR_CONSOLE_MENU_HPP
