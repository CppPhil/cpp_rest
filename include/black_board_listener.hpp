#ifndef INCG_CR_BLACK_BOARD_LISTENER_HPP
#define INCG_CR_BLACK_BOARD_LISTENER_HPP
#include "except.hpp" // cr::SocketErrorException
#include "byte.hpp" // cr::Byte
#include <netinet/in.h> // struct sockaddr_in
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstddef> // std::size_t
#include <cstdint> // std::uint16_t
#include <string> // std::string
#include <vector> // std::vector

namespace cr
{
class BlackBoardListener
    : private boost::noncopyable
{
public:
    using this_type = BlackBoardListener;

    BlackBoardListener();

    ~BlackBoardListener();

    this_type &receiveData();

    const std::vector<Byte> &getRecvBuf() const noexcept;

    boost::string_ref getBlackBoardIp() const noexcept;

    std::uint16_t getBlackBoardPort() const noexcept;

private:
    static const std::uint16_t s_blackBoardPort;

    static const std::size_t s_recvBufSiz;

    std::vector<Byte> m_recvBuf;
    std::string m_blackBoardIp;
    std::uint16_t m_blackBoardPort;
    struct sockaddr_in m_localSockAddr;
    struct sockaddr_in m_blackBoardSockAddr;
    int m_socket;
};
} // namespace cr
#endif // INCG_CR_BLACK_BOARD_LISTENER_HPP
