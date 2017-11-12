#ifndef INCG_CR_BLACK_BOARD_INFO_HPP
#define INCG_CR_BLACK_BOARD_INFO_HPP
#include <cstdint> // std::uint16_t
#include <string> // std::string
#include <iosfwd> // std::ostream &

namespace cr
{
/*!
 * \brief Type to store information that was received from the
 *        BlackBoard broadcast message.
**/
struct BlackBoardInfo
{
    /*!
     * \brief Starts a UDP socket and listens for the BlackBoard broadcast
     *        message, which is then received and used to create a
     *        BlackBoardInfo object.
     * \return The BlackBoardInfor object created.
    **/
    static BlackBoardInfo create();

    std::string ipAddress; /*!< The IP address of the BlackBoard */
    std::uint16_t senderPort; /*!< The sender UDP port of the BlackBoard */
    std::uint16_t portFromMessage; /*!< The port contained in the JSON send
                                    *   by the BlackBoard.
                                    *   This is where the BlackBoardRegistration
                                    *   will want to send requests to.
                                   **/
    std::uint16_t blackBoardPort = 24000U;
};

/*!
 * \brief Prints a BlackBoardInfo object to an ostream.
 * \param os The ostream to print to.
 * \param blackBoardInfo The object to print.
 * \return A reference to 'os'.
**/
std::ostream &operator<<(
    std::ostream &os,
    const BlackBoardInfo &blackBoardInfo);
} // namespace cr
#endif // INCG_CR_BLACK_BOARD_INFO_HPP
