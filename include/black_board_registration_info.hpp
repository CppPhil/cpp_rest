#ifndef INCG_CR_BLACK_BOARD_REGISTRATION_INFO_HPP
#define INCG_CR_BLACK_BOARD_REGISTRATION_INFO_HPP
#include <string> // std::string

namespace cr
{
struct BlackBoardRegistrationInfo
{
    BlackBoardRegistrationInfo(std::string p_userName, std::string p_passWord);

    std::string userName;
    std::string passWord;
};
} // namespace cr
#endif // INCG_CR_BLACK_BOARD_REGISTRATION_INFO_HPP
