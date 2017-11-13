#ifndef INCG_CR_APPLICATION_STATE_HPP
#define INCG_CR_APPLICATION_STATE_HPP
#include "../include/black_board_info.hpp" // cr::BlackBoardInfo
#include "../include/black_board_registration_info.hpp" // cr::BlackBoardRegistrationInfo
#include "../include/login_response.hpp" // cr::LoginResponse
#include "../include/quest.hpp" // cr::Quest
#include <gsl/gsl> // gsl::not_null
#include <boost/optional.hpp> // boost::optional
#include <ostream> // std::ostream
#include <istream> // std::istream
#include <vector> // std::vector

namespace cr
{
/*!
 * \brief Type for the current state of the application.
 * \note Used by the Application type.
 *       Passed to the ConsoleMenuItems' actions when they're run.
**/
struct ApplicationState
{
    /*!
     * \brief Creates an ApplicationState object.
     * \param os The ostream to use. This ostream shall be passed in
     *           by the Application class and shall be the one that it uses.
     * \param is The istream to use. This isteam shall be passed in by the
     *           Application class and shall be the one that it uses.
    **/
    ApplicationState(std::ostream &os, std::istream &is);

    gsl::not_null<std::ostream *> ostream; /*!< The ostream that the MenuItems'
                                            *   actions will print to
                                            **/
    gsl::not_null<std::istream *> istream; /*!< The istream that the MenuItems'
                                            *   actions can read from
                                           **/
    boost::optional<BlackBoardInfo> blackBoardInfo; /*!< The BlackBoardInfo */

    boost::optional<BlackBoardRegistrationInfo> blackBoardRegistrationInfo; /*!< Has the password and
                                                                             *   user name
                                                                            **/
    boost::optional<LoginResponse> loginResponse; /*!< the response received from the
                                                   *   login menu item's action.
                                                  **/
    std::vector<Quest> quests; /*!< The quests available */
};
} // namespace cr
#endif // INCG_CR_APPLICATION_STATE_HPP
