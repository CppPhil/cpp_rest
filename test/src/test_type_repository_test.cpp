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

TEST_CASE("count_test_type_test")
{
    cr::TestTypeRepository::create("myText", 1234U);

    CHECK(cr::TestTypeRepository::count() == 1U);

    const cr::TestType objectCreated{
        cr::TestTypeRepository::create("AnotherText", 12U)
    };

    CHECK(cr::TestTypeRepository::count() == 2U);

    cr::TestTypeRepository::create("more text", 1346425U);

    CHECK(cr::TestTypeRepository::count() == 3U);

    cr::TestTypeRepository::deleteOne(objectCreated.getId());

    CHECK(cr::TestTypeRepository::count() == 2U);

    cr::TestTypeRepository::deleteAll();

    CHECK(cr::TestTypeRepository::count() == 0U);
}

TEST_CASE("read_all_test_type")
{
    std::vector<cr::TestType> container{
      cr::TestTypeRepository::readAll()
    };

    CHECK(container.empty());

    cr::TestTypeRepository::create("Sample Text", 25U);
    cr::TestTypeRepository::create("More Sample Text", 5U);

    container = cr::TestTypeRepository::readAll();

    REQUIRE(container.size() == 2U);

    CHECK(container[0U].getNum() == 25U);
    CHECK(container[0U].getStr() == "Sample Text");
    CHECK(container[1U].getNum() == 5U);
    CHECK(container[1U].getStr() == "More Sample Text");

    cr::TestTypeRepository::deleteOne(container[0U].getId());

    container = cr::TestTypeRepository::readAll();

    REQUIRE(container.size() == 1U);

    CHECK(container[0U].getNum() == 5U);
    CHECK(container[0U].getStr() == "More Sample Text");

    cr::TestTypeRepository::deleteAll();

    container = cr::TestTypeRepository::readAll();

    CHECK(container.empty());
}
