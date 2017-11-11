#ifndef INCG_CR_BLACK_BOARD_INFO_HPP
#define INCG_CR_BLACK_BOARD_INFO_HPP
#include <cstdint> // std::uint16_t
#include <string> // std::string
#include <iosfwd> // std::ostream &

namespace cr
{
struct BlackBoardInfo
{
    static BlackBoardInfo create();

    std::string ipAddress;
    std::uint16_t port;
    std::uint16_t portFromMessage;
};

std::ostream &operator<<(
    std::ostream &os,
    const BlackBoardInfo &blackBoardInfo);
} // namespace cr
#endif // INCG_CR_BLACK_BOARD_INFO_HPP
