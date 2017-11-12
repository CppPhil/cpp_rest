#ifndef INCG_CR_CONSOLE_MENU_ITEM_HPP
#define INCG_CR_CONSOLE_MENU_ITEM_HPP
#include "../include/application_state.hpp" // cr::ApplicationState
#include <gsl/gsl> // gsl::not_null
#include <cstdint> // std::uint64_t
#include <iosfwd> // std::ostream
#include <string> // std::string
#include <functional> // std::function

namespace cr
{
/*!
 * \brief Type for the Items in the ConsoleMenu.
**/
class ConsoleMenuItem
{
public:
    using this_type = ConsoleMenuItem;

    /*!
     * \brief Type that defines enumerators identifying the ConsoleMenuItems.
    **/
    enum class Identifier : std::uint64_t
    {
        None, /*!< The none task -> does nothing */
        ExitApplication, /*!< The user wishes to exit the application */
        DiscoverBlackBoard, /*!< The discover BlackBoard task */
        RegisterUser /*!< The register a user with the BlackBoard task */
    };

    /*!
     * \brief Creates a ConsoleMenuItem
     * \param identifier The identifier that identifies this ConsoleMenuItem.
     * \param applicationState The application state that the action may modify
     *                         when called, given by the Application class.
     * \param text The text to show in the ConsoleMenu when displaying this
     *             item as a menu option.
     * \param action The action to run when this ConsoleMenuItem is selected
     *               by the user.
    **/
    ConsoleMenuItem(
        Identifier identifier,
        ApplicationState &applicationState,
        std::string text,
        std::function<void (ApplicationState &)> action);

    /*!
     * \brief Prints the text of this MenuItem.
     * \param ostream The ostream to print to.
     * \return A reference to this object.
    **/
    this_type &display(std::ostream &ostream);

    /*!
     * \brief Runs the action of this menu item by invoking it with the
     *        application state.
     * \return A reference to this object.
    **/
    this_type &runAction();

    /*!
     * \brief Returns the identifier of this object.
     * \return The identifier of this object.
    **/
    Identifier getIdentifier() const noexcept;

private:
    Identifier m_identifier; /*!< The identifier of this object */
    gsl::not_null<ApplicationState *> m_applicationState; /*!< The application
                                                           *   state, given by
                                                           *   the Application
                                                           *   class.
                                                          **/
    std::string m_text; /*!< The text to display for this menu item in the
                         *   ConsoleMenu
                        **/
    std::function<void (ApplicationState &)> m_action; /*!< The action to run
                                                        *   when this item is
                                                        *   selected.
                                                       **/
};
} // namespace cr
#endif // INCG_CR_CONSOLE_MENU_ITEM_HPP
