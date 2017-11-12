#ifndef INCG_CR_APPLICATION_STATE_HPP
#define INCG_CR_APPLICATION_STATE_HPP
#include "../include/black_board_info.hpp" // cr::BlackBoardInfo
#include <gsl/gsl> // gsl::not_null
#include <boost/optional.hpp> // boost::optional
#include <ostream> // std::ostream
#include <istream> // std::istream

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
    gsl::not_null<std::istream *> istream;
    boost::optional<BlackBoardInfo> blackBoardInfo;
};
} // namespace cr
#endif // INCG_CR_APPLICATION_STATE_HPP
