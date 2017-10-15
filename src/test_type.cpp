#include "../include/test_type.hpp"
#include <ciso646> // not
#include <utility> // std::move

namespace cr
{
TestType::TestType(std::string str, std::uint32_t num)
    : TestType{ std::move(str), num, 0U } // Creates an invalid object.
{
}

const std::string &TestType::getStr() const noexcept
{
    return m_str;
}

std::uint32_t TestType::getNum() const noexcept
{
    return m_num;
}

std::uint64_t TestType::getId() const noexcept
{
    return m_id;
}

TestType::TestType(std::string str, std::uint32_t num, std::uint64_t id)
    : m_id{ id },
      m_num{ num },
      m_str{ std::move(str) }
{
}

bool operator==(const TestType &lhs, const TestType &rhs)
{
    // Only need to compare the unique IDs.
    return lhs.getId() == rhs.getId();
}

bool operator!=(const TestType &lhs, const TestType &rhs)
{
    return not (lhs == rhs);
}
} // namespace cr
