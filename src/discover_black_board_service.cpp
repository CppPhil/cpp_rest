#include "../include/discover_black_board_service.hpp"
#include "../include/black_board_info.hpp" // cr::BlackBoardInfo::create

namespace cr
{
void discoverBlackBoardService(cr::ApplicationState &appState)
{
    appState.blackBoardInfo = cr::BlackBoardInfo::create();
    (*(appState.ostream)) << appState.blackBoardInfo.value() << '\n';
}
} // namespace cr
