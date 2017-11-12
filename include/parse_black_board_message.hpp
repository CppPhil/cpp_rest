#ifndef INCG_CR_PARSE_BLACK_BOARD_MESSAGE_HPP
#define INCG_CR_PARSE_BLACK_BOARD_MESSAGE_HPP
#include "byte.hpp" // cr::Byte
#include <cstdint> // std::uint16_t
#include <vector> // std::vector

namespace cr
{
/*!
 * \brief Function to extract the port that is contained in the BlackBoard
 *        broadcast message.
 * \param blackBoardMessage A read only reference to the vector that holds
 *                          the bytes of the BlackBoard message received.
 * \return The port extracted from 'blackBoardMessage'.
 * \throws InvalidJsonException if the JSON in 'blackBoardMessage' is malformed.
**/
std::uint16_t parseBlackBoardMessage(const std::vector<Byte> &blackBoardMessage);
} // namespace cr
#endif // INCG_CR_PARSE_BLACK_BOARD_MESSAGE_HPP
