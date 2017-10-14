#include <doctest.h>
#include "../../include/test_type.hpp" // cr::TestType
#include "../../include/test_type_repository.hpp" // cr::TestTypeRepository
#include <string> // std::string
#include <cstdint> // std::uint32_t, std::uint64_t

TEST_CASE("create_test_type")
{
    const std::string string{ "This is a text" };
    static constexpr std::uint32_t number{ 25U };

    const cr::TestType testType{
        cr::TestTypeRepository::create(string, number)
    };

    // The values should match.
    CHECK(testType.getNum() == number);
    CHECK(testType.getStr() == string);

    const std::uint64_t id{ testType.getId() };

    // the ID should not be 0
    CHECK(id != 0U);

    // It must exist in the DB
    CHECK(cr::TestTypeRepository::exists(id));

    // Delete it.
    cr::TestTypeRepository::deleteOne(id);

    // It must no longer exist in the DB.
    CHECK_FALSE(cr::TestTypeRepository::exists(id));
}

TEST_CASE("read_test_type")
{
    const std::string str{ "My favorite text" };
    static constexpr std::uint32_t num{ 1234U };

    const cr::TestType object{ cr::TestTypeRepository::create(str, num) };

    // check if it exists.
    CHECK(cr::TestTypeRepository::exists(object.getId()));

    boost::optional<cr::TestType> optional{
        cr::TestTypeRepository::read(object.getId())
    };

    REQUIRE(static_cast<bool>(optional));

    const cr::TestType objectRead{
        *optional
    };

    CHECK(objectRead == object);

    cr::TestTypeRepository::deleteOne(object.getId());

    CHECK_FALSE(cr::TestTypeRepository::exists(object.getId()));
}

TEST_CASE("update_test_type")
{
    const std::string s{ "Sample Text" };
    static constexpr std::uint32_t number{ 123U };

    const cr::TestType instance{ cr::TestTypeRepository::create(s, number) };

    const std::uint64_t id{ instance.getId() };

    CHECK(cr::TestTypeRepository::exists(id));

    // Update the tuple with a new number and a new string.
    static constexpr std::uint32_t newNumber{ 5U };
    static const std::string newString{ "New text" };

    const cr::TestType newInstance{
        cr::TestTypeRepository::update(id, newNumber, newString)
    };

    CHECK(cr::TestTypeRepository::exists(id));

    boost::optional<cr::TestType> optional{
        cr::TestTypeRepository::read(id)
    };

    REQUIRE(static_cast<bool>(optional));

    const cr::TestType justRead{
        *optional
    };

    // The ID must still be the same.
    CHECK(justRead.getId() == id);

    // The number must be the new one.
    CHECK(justRead.getNum() == newNumber);

    // The string must be the new one.
    CHECK(justRead.getStr() == newString);

    cr::TestTypeRepository::deleteOne(id);

    CHECK_FALSE(cr::TestTypeRepository::exists(id));
}
