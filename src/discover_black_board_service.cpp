#include "../include/discover_black_board_service.hpp"
#include "../include/black_board_info.hpp" // cr::BlackBoardInfo::create
#include <ciso646> // not

namespace cr
{
void discoverBlackBoardService(cr::ApplicationState &appState)
{
    appState.blackBoardInfo = cr::BlackBoardInfo::create();
    const boost::optional<cr::BlackBoardInfo> &opt{ appState.blackBoardInfo };

    if (not opt) {
        CR_THROW_WITH_SOURCE_INFO(
            OptionalHadNoValueException,
            "appState.blackBoardInfo had no value!");
    }

    (*(appState.ostream)) << (*(appState.blackBoardInfo)) << '\n';
}
} // namespace cr
