#include "../include/black_board_registration_info.hpp"
#include <utility> // std::move

namespace cr
{
BlackBoardRegistrationInfo::BlackBoardRegistrationInfo(
    std::string p_userName,
    std::string p_passWord)
    : userName{ std::move(p_userName) },
      passWord{ std::move(p_passWord) }
{
}
} // namespace cr
