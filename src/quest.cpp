#include "../include/quest.hpp"
#include "../include/json.hpp" // cr::fetchString
#include <ciso646> // not
#include <utility> // std::move
#include <iterator> // std::begin, std::end, std::back_inserter
#include <algorithm> // std::transform

namespace cr
{
Quest Quest::fromJson(const json::GenericValue<json::UTF8<>> &object)
{
    const std::string description{ fetchString("description", object) };
    const std::int64_t id{ fetchInt64("id", object) };
    const std::string name{ fetchString("name", object) };
    const std::string requirements{
        [&object] {
            std::string retVal{ };
            try {
                retVal = fetchString("requirements", object);
            } catch (const InvalidJsonException &) {
                retVal = "";
            }

            return retVal;
        }()
    };
    const std::int64_t reward{ fetchInt64("reward", object) };
    const json::GenericValue<json::UTF8<>>::ConstArray array{
        fetchArray("tasks", object)
    };

    std::vector<std::string> tasks{ };

    std::transform(std::begin(array), std::end(array), std::back_inserter(tasks),
                   [](const json::GenericValue<json::UTF8<>> &e) {
        if (not e.IsString()) {
            CR_THROW_WITH_SOURCE_INFO(
                InvalidJsonException,
                "json array contained invalid value.");
        }

        return e.GetString();
    });

    return { description, id, name, requirements, reward, tasks };
}

Quest::Quest(
    std::string description,
    std::int64_t id,
    std::string name,
    std::string requirements,
    std::int64_t reward,
    std::vector<std::string> tasks)
    : m_description{ std::move(description) },
      m_id{ id },
      m_name{ std::move(name) },
      m_requirements{ std::move(requirements) },
      m_reward{ reward },
      m_tasks{ std::move(tasks) }
{
}

boost::string_ref Quest::getDescription() const noexcept
{
    return m_description;
}

std::int64_t Quest::getId() const noexcept
{
    return m_id;
}

boost::string_ref Quest::getName() const noexcept
{
    return m_name;
}

boost::string_ref Quest::getRequirements() const noexcept
{
    return m_requirements;
}

std::int64_t Quest::getReward() const noexcept
{
    return m_reward;
}

const std::vector<std::string> &Quest::getTasks() const noexcept
{
    return m_tasks;
}

bool operator==(const Quest &lhs, const Quest &rhs) noexcept
{
    return lhs.getId() == rhs.getId();
}

bool operator!=(const Quest &lhs, const Quest &rhs) noexcept
{
    return not (lhs == rhs);
}
} // namespace cr
