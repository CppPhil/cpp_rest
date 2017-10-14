#ifndef INCG_CR_TEST_TYPE_HPP
#define INCG_CR_TEST_TYPE_HPP
#include <cstdint> // std::uint32_t, std::uint64_t
#include <string> // std::string

namespace cr
{
class TestTypeRepository;

class TestType
{
public:
    using this_type = TestType;

    friend class TestTypeRepository;

    TestType(std::string str, std::uint32_t num);

    const std::string &getStr() const noexcept;

    std::uint32_t getNum() const noexcept;

    std::uint64_t getId() const noexcept;

private:
    TestType(std::string str, std::uint32_t num, std::uint64_t id);

    std::uint64_t m_id;
    std::uint32_t m_num;
    std::string m_str;
};

bool operator==(const TestType &lhs, const TestType &rhs);

bool operator!=(const TestType &lhs, const TestType &rhs);
} // namespace cr
#endif // INCG_CR_TEST_TYPE_HPP
