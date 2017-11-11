#include "../include/black_board_listener.hpp"
#include <arpa/inet.h> // htons, htonl
#include <boost/current_function.hpp> // BOOST_CURRENT_FUNCTION
#include <cstring> // std::memset
#include <exception> // std::terminate
#include <iostream> // std::cerr

namespace cr
{
BlackBoardListener::BlackBoardListener()
    : m_recvBuf(s_recvBufSiz, Byte{ }),
      m_blackBoardIp{ },
      m_blackBoardPort{ s_blackBoardPort },
      m_localSockAddr{ },
      m_blackBoardSockAddr{ },
      m_socket{ -1 } // invalid socket by default
{
    std::memset(&m_localSockAddr, 0, sizeof(m_localSockAddr));
    std::memset(&m_blackBoardSockAddr, 0, sizeof(m_blackBoardSockAddr));

    m_localSockAddr.sin_family      = AF_INET; // IPv4
    m_localSockAddr.sin_port        = htons(s_blackBoardPort);
    m_localSockAddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    //                IPv4   , for UDP   , UDP
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // if socket failed
    if (m_socket == -1) {
        CR_THROW_WITH_SOURCE_INFO(SocketErrorException, "socket failed!");
    }
}

BlackBoardListener::~BlackBoardListener()
{
    if (close(m_socket) == -1) {
        std::cerr << "Failed to close socket in "
                  << BOOST_CURRENT_FUNCTION << '\n';
        std::terminate();
    }
}

BlackBoardListener &BlackBoardListener::receiveData()
{
#if !defined(CI_APPVEYOR) && !defined(CI_TRAVIS)
    const int errCode{
        bind(
            m_socket,
            reinterpret_cast<const struct sockaddr *>(&m_localSockAddr),
            sizeof(m_localSockAddr))
    };

    // if an error occurred
    if (errCode == -1) {
        CR_THROW_WITH_SOURCE_INFO(SocketErrorException, "bind failed!");
    }

    static constexpr int noFlags{ 0 };

    socklen_t remoteSockAddrLen{ sizeof(m_blackBoardSockAddr) };

    const ssize_t bytesReceived{
        recvfrom(
            m_socket,
            m_recvBuf.data(),
            m_recvBuf.size(),
            noFlags,
            reinterpret_cast<struct sockaddr *>(&m_blackBoardSockAddr),
            &remoteSockAddrLen)
    };

    switch (bytesReceived) {
    case 0: // remote host shut down the connection
        CR_THROW_WITH_SOURCE_INFO(
            SocketErrorException,
            "The remote host shut down the connection.");
    case -1: // an error occurred
        CR_THROW_WITH_SOURCE_INFO(SocketErrorException, "recvfrom failed!");
    }

    // get rid of the excess bytes
    m_recvBuf.resize(static_cast<std::size_t>(bytesReceived));

    // fetch the info about the remote host.
    m_blackBoardIp = inet_ntoa(m_blackBoardSockAddr.sin_addr);
    m_blackBoardPort = ntohs(m_blackBoardSockAddr.sin_port);

#endif
    return *this;
}

const std::vector<Byte> &BlackBoardListener::getRecvBuf() const noexcept
{
    return m_recvBuf;
}

boost::string_ref BlackBoardListener::getBlackBoardIp() const noexcept
{
    return m_blackBoardIp;
}

std::uint16_t BlackBoardListener::getBlackBoardPort() const noexcept
{
    return m_blackBoardPort;
}

const std::uint16_t BlackBoardListener::s_blackBoardPort = 24000U;

const std::size_t BlackBoardListener::s_recvBufSiz = 1024U;
} // namespace cr
