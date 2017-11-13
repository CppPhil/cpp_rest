#ifndef INCG_CR_CREATE_QUESTS_HPP
#define INCG_CR_CREATE_QUESTS_HPP
#include "../include/quest.hpp" // cr::Quest
#include "../include/except.hpp" // cr::InvalidJsonException
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <vector> // std::vector

namespace cr
{
std::vector<Quest> createQuests(boost::string_ref jsonText);
} // namespace cr
#endif // INCG_CR_CREATE_QUESTS_HPP
