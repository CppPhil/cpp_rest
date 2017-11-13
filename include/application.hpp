#ifndef INCG_CR_APPLICATION_HPP
#define INCG_CR_APPLICATION_HPP
#include "../include/noncopyable.hpp" // CR_NONCOPYABLE
#include "../include/application_state.hpp" // cr::ApplicationState
#include "../include/console_menu.hpp" // cr::ConsoleMenu
#include "../include/console_menu_item.hpp" // cr::ConsoleMenuItem
#include "../include/rest_client.hpp" // cr::RestClient
#include "../include/except.hpp" // CR_THROW_WITH_SOURCE_INFO
#include <ostream> // std::ostream
#include <istream> // std::istream
#include <stdexcept> // std::logic_error

namespace cr
{
/*!
 * \brief Type representing the console application.
**/
class Application
{
public:
    using this_type = Application;

    CR_NONCOPYABLE(Application);

    /*!
     * \brief Initializes the console menu with the default items.
    **/
    Application();

    /*!
     * \brief Runs the application by running the console menu over and over
     *        again until the console menu has indicated that the user wishes
     *        to exit the application.
     * \return A reference to this object.
    **/
    this_type &start();

private:
    static std::ostream &s_ostream; /*!< The ostream to print to by default */
    static std::istream &s_istream; /*!< The istream to read from by default */

    /*!
     * \brief Helper function to easily create a ConsoleMenuItem.
     * \param identifier The identifier of the ConsoleMenuItem to create.
     * \param text The text to print for the option for the ConsoleMenuItem.
     * \param action The action to perform if the ConsoleMenuItem is selected.
     * \return The ConsoleMenuItem created.
    **/
    ConsoleMenuItem makeConsoleMenuItem(
        ConsoleMenuItem::Identifier identifier,
        std::string text,
        std::function<bool (ApplicationState &)> action);

    /*!
     * \brief Replaces the menu items in the console menu with the default ones.
    **/
    void setConsoleMenuToDefaultItems();

    /*!
     * \brief Creates the BlackBoardRegistration object in the optional.
     * \return bool if it could be created, false otherwise.
    **/
    bool createBlackBoardRegistration();

    boost::optional<RestClient> m_restClient;
    ApplicationState m_applicationState; /*!< The current application state */
    ConsoleMenu m_consoleMenu; /*!< The console menu */
    const ConsoleMenuItem m_exitApplication; /*!< The exit application menu item */
    const ConsoleMenuItem m_discoverBlackBoard; /*!< The discover BlackBoard menu item */
    const ConsoleMenuItem m_registerUser; /*!< The register a user with the BlackBoard menu item */
    const ConsoleMenuItem m_login; /*!< Login to the BlackBoard */
    const ConsoleMenuItem m_whoami; /*!< check the login with the BlackBoard */
    const ConsoleMenuItem m_fetchPublicQuests; /*!< get the public quests */
};
} // namespace cr
#endif // INCG_CR_APPLICATION_HPP
