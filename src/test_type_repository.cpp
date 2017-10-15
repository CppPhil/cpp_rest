#include "../include/test_type_repository.hpp"
#include "../include/database_session.hpp" // cr::DataBaseSession
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <ciso646> // not
#include <utility> // std::move
#include <string> // std::string, std::literals::string_literals::operator""s

namespace cr
{
namespace
{
constexpr char oneEntryExpectedErrorText[]
    = "Result set was empty, but should have contained one entry.";
} // anonymous namespace

TestType TestTypeRepository::create(std::string str, std::uint32_t num)
{
    sql << "INSERT INTO test_type(num,str) "
           "VALUES(?,?)"
        << num << str << cppdb::exec;

    return fetchLastCreated();
}

bool TestTypeRepository::exists(std::uint64_t id)
{
    // the value returned by the SQL database if there was a tuple with ID 'id'.
    static constexpr int trueValue{ 1 };

    // The query will return 1 if there is a tuple in test_type with the ID 'id'
    // otherwise it will return 0.
    cppdb::result res{
        sql << "SELECT COUNT(1) AS \"result\" "
               "FROM test_type "
               "WHERE id=?"
            << id << cppdb::row // fetch just the 1st row
    };

    if (res.empty()) {
        CR_THROW_WITH_SOURCE_INFO(
            FailedToFetchFromDatabaseException,
            oneEntryExpectedErrorText);
    }

    const int result{ res.get<int>("result") };

    return result == trueValue;
}

std::uint64_t TestTypeRepository::count()
{
    cppdb::result res{
        sql << "SELECT COUNT(*) AS \"result\" "
               "FROM test_type "
            << cppdb::row // fetch just one row
    };

    if (res.empty()) {
        CR_THROW_WITH_SOURCE_INFO(
            FailedToFetchFromDatabaseException,
            oneEntryExpectedErrorText);
    }

    return res.get<std::uint64_t>("result");
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
        return boost::none; // Create an empty optional.
    }

    return boost::make_optional(
        TestType{ getStr(res), getNum(res), getId(res) });
}

std::vector<TestType> TestTypeRepository::readAll()
{
    std::uint64_t currentId{ 0U };
    std::uint32_t currentNum{ 0U };
    std::string currentStr{ };

    cppdb::result result{
        sql << "SELECT id,num,str "
               "FROM test_type "
               "WHERE 1" // The where clause always evaluates to true
    };

    std::vector<TestType> retVal{ };

    // The vector will remain empty if there are no results.
    while (result.next()) {
        currentId  = result.get<std::uint64_t>("id");
        currentNum = result.get<std::uint32_t>("num");
        currentStr = result.get<std::string>("str");

        retVal.push_back(
            TestType{ std::move(currentStr), currentNum, currentId });
    }

    return retVal;
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

void TestTypeRepository::deleteAll()
{
    sql << "DELETE FROM test_type "
           "WHERE 1" // The where clause always evaluates to true
        << cppdb::exec;
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
            oneEntryExpectedErrorText);
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
