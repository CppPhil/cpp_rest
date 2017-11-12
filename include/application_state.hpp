#ifndef INCG_CR_APPLICATION_STATE_HPP
#define INCG_CR_APPLICATION_STATE_HPP
#include "../include/black_board_info.hpp" // cr::BlackBoardInfo
#include <gsl/gsl> // gsl::not_null
#include <boost/optional.hpp> // boost::optional
#include <ostream> // std::ostream
#include <istream> // std::istream

namespace cr
{
struct ApplicationState
{
    ApplicationState(std::ostream &os, std::istream &is);

    gsl::not_null<std::ostream *> ostream;
    gsl::not_null<std::istream *> istream;
    boost::optional<BlackBoardInfo> blackBoardInfo;
};
} // namespace cr
#endif // INCG_CR_APPLICATION_STATE_HPP
