#ifndef INCG_CR_DISCOVER_BLACK_BOARD_SERVICE_HPP
#define INCG_CR_DISCOVER_BLACK_BOARD_SERVICE_HPP
#include "../include/application_state.hpp" // cr::ApplicationState
#include "../include/except.hpp" // cr::OptionalHadNoValueException

namespace cr
{
/*!
 * \brief The action of the discovenr BlackBoard service ConsoleMenuItem.
 * \param appState The application state, given by the Application class.
 * \return true.
**/
bool discoverBlackBoardService(cr::ApplicationState &appState);
} // namespace cr
#endif // INCG_CR_DISCOVER_BLACK_BOARD_SERVICE_HPP
