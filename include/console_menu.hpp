#ifndef INCG_CR_CONSOLE_MENU_HPP
#define INCG_CR_CONSOLE_MENU_HPP
#include "../include/console_menu_item.hpp" // cr::ConsoleMenuItem
#include "../include/invoke.hpp" // cr::invoke
#include <boost/optional.hpp> // boost::optional
#include <gsl/gsl> // gsl::not_null
#include <cstddef> // std::size_t
#include <ostream> // std::ostream
#include <istream> // std::istream
#include <iterator> // std::iterator_traits, std::begin, std::end
#include <string> // std::string
#include <vector> // std::vector
#include <type_traits> // std::is_same
#include <algorithm> // std::remove_if, std::sort

namespace cr
{
/*!
 * \brief Type representing the console menu.
**/
class ConsoleMenu
{
public:
    /*!
     * \brief The type that is stored in the container of ConsoleMenu.
    **/
    struct value_type
    {
        /*!
         * \brief Constructs a value_type.
         * \param p_menuItem The menu item to use.
         * \note the boolean data member will be false by default.
        **/
        explicit value_type(ConsoleMenuItem p_menuItem);

        ConsoleMenuItem menuItem; /*!< The menu item. */
        bool wasActionExecutedSuccessfully; /*!< This boolean shall be true
                                             *   if the menuItem's action was
                                             *   executed and that execution
                                             *   indicated success. Otherwise
                                             *   it shall be false.
                                            **/
    };

    using this_type = ConsoleMenu;
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
            ConsoleMenuItem>::value, "Invalid iterator type in ConsoleMenu::addItems.");

        for (; first != last; ++first) {
            addItem(*first);
        }

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
     * \brief Removes all the value_types that satisfy the given predicate.
     * \param unaryPredicate The predicate that shall return true when invoked
     *                       if the value_type passed to it shall be removed.
     * \return A reference to this object.
    **/
    template <typename UnaryPredicate>
    this_type &eraseIf(UnaryPredicate unaryPredicate)
    {
        m_cont.erase(
            std::remove_if(
                std::begin(m_cont),
                std::end(m_cont),
                [&unaryPredicate](const value_type &elem) {
                    return ::cr::invoke(unaryPredicate, elem);
                }),
            std::end(m_cont));
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

    /*!
     * \brief Finds a ConsoleMenuItem by identifier.
     * \return A pointer to the ConsoleMenuItem found, or nullptr
     *         if there is no ConsoleMenuItem with the identifier passed in.
    **/
    const ConsoleMenuItem *findByIdentifier(
        ConsoleMenuItem::Identifier identifier) const noexcept;

    /*!
     * \brief Determines whether or not a ConsoleMenuItem identified by the
     *        identifier given has had its action successfully executed.
     * \param identifier The identifier of the ConsoleMenuItem to get the
     *                   execution status for its action of.
     * \return true if the action associated with the ConsoleMenuItem identified
     *         by 'identifier' was executed successfully, false otherwise.
     * \note Will return false if the action has not been executed and will
     *       return false if there is no ConsoleMenuItem with the identifier
     *       'identifier' in the ConsoleMenu.
    **/
    bool getExecutionStatus(
        ConsoleMenuItem::Identifier identifier) const noexcept;

    /*!
     * \brief Returns a reference to the menu item last executed.
     * \return A reference to the menu item last executed.
     * \warning May only be called just after having executed the menu item.
     *          The menu item last executed may not have been removed from
     *          this ConsoleMenu before calling this function.
    **/
    const value_type &getLastExecuted() const;

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
     * \return true if the action was run successfully, false otherwise.
    **/
    bool runByIndex(std::size_t idx);

    /*!
     * \brief Returns the iterator to the value_type that has the
     *        ConsoleMenuItem with the identifier 'identifier.'
     * \param identifier The identifier to search with.
     * \return The iterator. May be the end iterator if nothing was found.
    **/
    container_type::const_iterator findByIdentifierHelper(
        ConsoleMenuItem::Identifier identifier) const noexcept;

    container_type m_cont; /*!< The menu items and their associated bools. */
    gsl::not_null<std::ostream *> m_ostream; /*!< The ostream given by
                                              *   the Application class.
                                             **/
    gsl::not_null<std::istream *> m_istream; /*!< The istream given by
                                              *   the Application class.
                                             **/
    std::size_t m_lastExecuted; /*!< Index of the last menu item that had its
                                 *   action run.
                                **/
};
} // namespace cr
#endif // INCG_CR_CONSOLE_MENU_HPP
