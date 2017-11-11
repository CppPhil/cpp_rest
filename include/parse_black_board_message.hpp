#ifndef INCG_CR_PARSE_BLACK_BOARD_MESSAGE_HPP
#define INCG_CR_PARSE_BLACK_BOARD_MESSAGE_HPP
#include "byte.hpp" // cr::Byte
#include <cstdint> // std::uint16_t
#include <vector> // std::vector

namespace cr
{
std::uint16_t parseBlackBoardMessage(const std::vector<Byte> &blackBoardMessage);
} // namespace cr
#endif // INCG_CR_PARSE_BLACK_BOARD_MESSAGE_HPP
