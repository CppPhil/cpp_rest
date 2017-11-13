#ifndef INCG_CR_QUEST_HPP
#define INCG_CR_QUEST_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/except.hpp" // cr::InvalidJsonException
#include <rapidjson/document.h> // rapidjson::GenericValue
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstdint> // std::int64_t
#include <string> // std::string
#include <vector> // std::vector

namespace cr
{
class Quest
{
public:
    using this_type = Quest;

    static Quest fromJson(
        const json::GenericValue<json::UTF8<>> &object);

    Quest(
        std::string description,
        std::int64_t id,
        std::string name,
        std::string requirements,
        std::int64_t reward,
        std::vector<std::string> tasks);

    boost::string_ref getDescription() const noexcept;

    std::int64_t getId() const noexcept;

    boost::string_ref getName() const noexcept;

    boost::string_ref getRequirements() const noexcept;

    std::int64_t getReward() const noexcept;

    const std::vector<std::string> &getTasks() const noexcept;

private:
    std::string m_description;
    std::int64_t m_id;
    std::string m_name;
    std::string m_requirements;
    std::int64_t m_reward;
    std::vector<std::string> m_tasks;
};

bool operator==(const Quest &lhs, const Quest &rhs) noexcept;

bool operator!=(const Quest &lhs, const Quest &rhs) noexcept;
} // namespace cr
#endif // INCG_CR_QUEST_HPP
