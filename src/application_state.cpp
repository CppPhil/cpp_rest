#include "../include/application_state.hpp"

namespace cr
{
ApplicationState::ApplicationState(std::ostream &os, std::istream &is)
    : ostream{ &os },
      istream{ &is },
      blackBoardInfo{ boost::none },
      blackBoardRegistrationInfo{ boost::none },
      loginResponse{ boost::none }
{
}
} // namespace cr
