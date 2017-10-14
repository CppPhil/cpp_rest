#include "../include/test_type_repository.hpp"
#include "../include/database_session.hpp" // cr::DataBaseSession
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <ciso646> // not
#include <utility> // std::move
#include <string> // std::string, std::literals::string_literals::operator""s

namespace cr
{
TestType TestTypeRepository::create(std::string str, std::uint32_t num)
{
    sql << "INSERT INTO test_type(num,str) "
           "VALUES(?,?)"
        << num << str << cppdb::exec;

    return fetchLastCreated();
}

boost::optional<TestType> TestTypeRepository::read(std::uint64_t id)
{
    // get one row, with the id 'id' from the table test_type.
    cppdb::result res{
        sql << "SELECT id,num,str "
               "FROM test_type "
               "WHERE id=?"
            << id << cppdb::row
    };

    if (res.empty()) {
        return boost::none;
    }

    return boost::make_optional(
        TestType{ getStr(res), getNum(res), getId(res) });
}

TestType TestTypeRepository::update(
    std::uint64_t id,
    std::uint32_t num,
    std::string str)
{
    using namespace std::literals::string_literals;

    sql << "UPDATE test_type "
           "SET num = ?, str = ? "
           "WHERE id=?"
        << num << str << id
        << cppdb::exec;

    boost::optional<cr::TestType> optional{ read(id) };

    if (not optional) {
        CR_THROW_WITH_SOURCE_INFO(
            FailedToFetchFromDatabaseException,
            "update failed for id "s
            + boost::lexical_cast<std::string>(id));
    }

    return *optional; // only access the value if there actually is one.
}

void TestTypeRepository::deleteOne(std::uint64_t id)
{
    sql << "DELETE FROM test_type "
           "WHERE id=?"
        << id << cppdb::exec;
}

bool TestTypeRepository::exists(std::uint64_t id)
{
    cppdb::result res{
        sql << "SELECT COUNT(1) AS \"result\" "
               "FROM test_type "
               "WHERE id=?"
            << id << cppdb::row // fetch just the 1st row
    };

    if (res.empty()) {
        CR_THROW_WITH_SOURCE_INFO(
            FailedToFetchFromDatabaseException,
            "Result set was empty, but should have contained one entry.");
    }

    const int result{ res.get<int>("result") };

    return result == 1;
}

TestType TestTypeRepository::fetchLastCreated()
{
    cppdb::result res{
        sql << "SELECT id,num,str FROM test_type WHERE id= "
               "(SELECT MAX(id)"
               "FROM test_type)" << cppdb::row // fetch just the 1st row
    };

    if (res.empty()) {
        CR_THROW_WITH_SOURCE_INFO(
            FailedToFetchFromDatabaseException,
            "Result set was empty, but should have contained one entry");
    }

    return TestType{ getStr(res), getNum(res), getId(res) };
}

std::string TestTypeRepository::getStr(cppdb::result &res)
{
    return res.get<std::string>("str");
}

std::uint32_t TestTypeRepository::getNum(cppdb::result &res)
{
    return res.get<std::uint32_t>("num");
}

std::uint64_t TestTypeRepository::getId(cppdb::result &res)
{
    return res.get<std::uint64_t>("id");
}

cppdb::session &TestTypeRepository::sql = DataBaseSession::getInstance();
} // namespace cr
