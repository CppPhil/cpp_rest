#include "../include/black_board_info.hpp"
#include "../include/black_board_listener.hpp" // cr::BlackBoardListener
#include "../include/parse_black_board_message.hpp" // cr::parseBlackBoardMessage
#include <ostream> // std::ostream

namespace cr
{
BlackBoardInfo BlackBoardInfo::create()
{
    BlackBoardListener blackBoardListener{ };
    blackBoardListener.receiveData();

    return BlackBoardInfo{
        blackBoardListener.getBlackBoardIp().data(),
        blackBoardListener.getBlackBoardPort(),
        cr::parseBlackBoardMessage(blackBoardListener.getRecvBuf())
    };
}

std::ostream &operator<<(
    std::ostream &os,
    const BlackBoardInfo &blackBoardInfo)
{
    return os << "black board info:\n"
              << "IP address: "        << blackBoardInfo.ipAddress << '\n'
              << "port: "              << blackBoardInfo.port      << '\n'
              << "port from message: " << blackBoardInfo.portFromMessage;
}
} // namespace cr