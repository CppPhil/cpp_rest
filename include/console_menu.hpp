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
#include <algorithm> // std::copy, std::remove_if, std::sort

namespace cr
{
/*!
 * \brief Type representing the console menu.
**/
class ConsoleMenu
{
public:
    using this_type = ConsoleMenu;
    using value_type = ConsoleMenuItem;
    using container_type = std::vector<value_type>;

    /*!
     * \brief Creates the ConsoleMenu.
     * \param ostream The ostream given by the Application class.
     * \param istream The istream given by the Application class.
    **/
    ConsoleMenu(std::ostream &ostream, std::istream &istream);

    /*!
     * \brief Adds an lvalue menu item.
     * \param menuItem The menu item to add.
     * \return A reference to this object.
    **/
    this_type &addItem(const ConsoleMenuItem &menuItem);

    /*!
     * \brief Adds an rvalue menu item.
     * \param menuItem The menu item to add.
     * \return A reference to this object.
    **/
    this_type &addItem(ConsoleMenuItem &&menuItem) noexcept;

    /*!
     * \brief Adds a range of ConsoleMenuItems denoted by two iterators.
     * \param first The begin iterator of the range.
     * \param last The end iterator of the range.
     * \return A reference to this object.
    **/
    template <typename InputIterator>
    this_type &addItems(InputIterator first, InputIterator last)
    {
        static_assert(std::is_same<
            typename std::iterator_traits<InputIterator>::value_type,
            value_type>::value, "Invalid iterator type in ConsoleMenu::addItems.");
        std::copy(first, last, std::back_inserter(m_menuItems));
        return *this;
    }

    /*!
     * \brief Removes all MenuItems.
     * \return A reference to this object.
    **/
    this_type &clear();

    /*!
     * \brief Returns the amount of menu items that this object contains.
     * \return The amount of menu itemns that this object contains.
    **/
    container_type::size_type size() const noexcept;

    /*!
     * \brief Replaces the current menu items with the ones from a range
     *        denoted by iterators.
     * \param first The begin iterator of the range.
     * \param last The end iterator of the range.
     * \return A reference to this object.
    **/
    template <typename InputIterator>
    this_type &replaceItems(InputIterator first, InputIterator last)
    {
        clear();
        return addItems(first, last);
    }

    /*!
     * \brief Removes all ConsoleMenuItems that have the identifier passed in.
     * \param identifier The identifier of the ConsoleMenuItem to delete.
     * \return A reference to this object.
    **/
    this_type &erase(ConsoleMenuItem::Identifier identifier);

    /*!
     * \brief Removes all the ConsoleMenuItems that satisfy the given predicate.
     * \param unaryPredicate The predicate that shall return true when invoked
     *                       if the ConsoleMenuItem passed to it shall be removed.
     * \return A reference to this object.
    **/
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

    /*!
     * \brief Runs the ConsoleMenu by printing the available options and
     *        prompting the user for input until a valid input is entered.
     *        As soon as a valid input is entered the associated menu item's
     *        action is run.
     * \return The identifier of the ConsoleMenuItem that had its action run.
    **/
    ConsoleMenuItem::Identifier run();

    /*!
     * \brief Sorts the ConsoleMenuItem so that the ConsoleMenuItems with
     *        the lower integer values for their Identifiers come last.
     * \return A reference to this object.
    **/
    this_type &sort();

private:
    static const std::size_t s_offset; /*!< Offset translating from 0 and 1
                                        *   based indexing and vice versa.
                                       **/
    static const int s_idxWidth; /*!< The width of an index when printing it */

    static const int s_defaultWidth; /*!< The default width, to be used when not
                                      *   printing an index.
                                     **/
    static const char s_promptText[]; /*!< The text prompting the user to enter
                                       *   a valid index, after having printed
                                       *   the available options.
                                      **/

    /*!
     * \brief Prints all the options available.
     * \param ostream The ostream to print to.
    **/
    void displayItems(std::ostream &ostream);

    /*!
     * \brief Prompts the user for input.
     *        To be used after having printed the options available.
     * \param ostream The ostream to print to.
    **/
    void displayPrompt(std::ostream &ostream);

    /*!
     * \brief Function to attempt to read one time.
     * \param istream The istream to try to read an index from.
     * \return boost::none if reading failed, or an optional containing the
     *         value read if reading succeeded.
    **/
    boost::optional<std::size_t> readInput(std::istream &istream);

    /*!
     * \brief Function to check whether or not a user input is valid.
     * \param inputLine The line that was successfully read.
     * \return true if the input is considered valid, false otherwise.
    **/
    bool isInputValid(const std::string &inputLine);

    /*!
     * \brief Runs the action of the MenuItem at index 'idx'.
     * \param idx The zero-based index of the MenuItem that shall have its
     *            action run.
    **/
    void runByIndex(std::size_t idx);

    container_type m_menuItems; /*!< The menu items */
    gsl::not_null<std::ostream *> m_ostream; /*!< The ostream given by
                                              *   the Application class.
                                             **/
    gsl::not_null<std::istream *> m_istream; /*!< The istream given by
                                              *   the Application class.
                                             **/
};
} // namespace cr
#endif // INCG_CR_CONSOLE_MENU_HPP
