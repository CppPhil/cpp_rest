#include "../include/discover_black_board_service.hpp"
#include "../include/black_board_info.hpp" // cr::BlackBoardInfo::create
#include "../include/safe_optional_access.hpp" // cr::safeOptionalAccess

namespace cr
{
void discoverBlackBoardService(cr::ApplicationState &appState)
{
    appState.blackBoardInfo = cr::BlackBoardInfo::create(); // this call will block.

    const boost::optional<cr::BlackBoardInfo> &opt{ appState.blackBoardInfo };

    (*(appState.ostream)) << safeOptionalAccess(opt) << '\n';
}
} // namespace cr
