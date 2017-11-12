#ifndef INCG_CR_BLACK_BOARD_LISTENER_HPP
#define INCG_CR_BLACK_BOARD_LISTENER_HPP
#include "except.hpp" // cr::SocketErrorException
#include "byte.hpp" // cr::Byte
#ifndef _WIN32
#   include <netinet/in.h> // struct sockaddr_in
#endif
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstddef> // std::size_t
#include <cstdint> // std::uint16_t
#include <string> // std::string
#include <vector> // std::vector

namespace cr
{
/*!
 * \brief Type to listen for the BlackBoard broadcast message.
 * \note Used in cr::BlackBoardInfo::create().
**/
class BlackBoardListener
    : private boost::noncopyable
{
public:
    using this_type = BlackBoardListener;

    /*!
     * \brief Creates a BlackBoardListener.
     * \throws SocketErrorException if the UDP socket could not be created.
    **/
    BlackBoardListener();

    /*!
     * \brief Destroys a BlackBoardListener.
     * \warning May call std::terminate() if the socket could not be closed.
    **/
    ~BlackBoardListener();

    /*!
     * \brief Binds the socket and wait for data to be received.
     *        After having received data, the information required is extracted
     *        from the data received.
     * \return A reference to this object.
     * \warning This is a blocking call.
     * \throws SocketErrorException on error.
     * \note This function must be called before calling getRecvBuf,
     *       getBlackBoardIp, or getBlackBoardPort.
    **/
    this_type &receiveData();

    /*!
     * \brief Returns a read only reference to the receive buffer of this
     *        object.
     * \return A read only reference to the receive buffer of this object.
     * \warning Should only be called after having called receiveData().
    **/
    const std::vector<Byte> &getRecvBuf() const noexcept;

    /*!
     * \brief Returns a string_ref to the BlackBoard IP address string.
     * \return A string_ref to the BlackBoard IP address string.
     * \warning Should only be called after having called receiveData().
    **/
    boost::string_ref getBlackBoardIp() const noexcept;

    /*!
     * \brief Returns the BlackBoard UDP sender port.
     * \return The BlackBoard UDP sender port.
     * \warning Should only be called after having called receiveData().
    **/
    std::uint16_t getBlackBoardPort() const noexcept;

private:
    static const std::uint16_t s_blackBoardPort; /*!< The UDP port to listen on */

    static const std::size_t s_recvBufSiz; /*!< The default size of the receive buffer */

    std::vector<Byte> m_recvBuf; /*!< The receive buffer */
    std::string m_blackBoardIp; /*!< Will store the IP address of the BlackBoard */
    std::uint16_t m_blackBoardPort; /*!< Will store the UDP sender port of the BlackBoard */
#ifndef _WIN32
    struct sockaddr_in m_localSockAddr; /*!< The socket address to use for the listen socket */
    struct sockaddr_in m_blackBoardSockAddr; /*!< The socket address for the BlackBoard */
#endif
    int m_socket; /*!< The UDP listen socket to use */
};
} // namespace cr
#endif // INCG_CR_BLACK_BOARD_LISTENER_HPP
