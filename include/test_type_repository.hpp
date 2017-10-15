#ifndef INCG_CR_TEST_TYPE_REPOSITORY_HPP
#define INCG_CR_TEST_TYPE_REPOSITORY_HPP
#include "../include/test_type.hpp" // cr::TestType
#include "../include/compiler.hpp" // CR_COMPILER, CR_COMPILER_GCC
#include "../include/except.hpp" // cr::FailedToFetchFromDatabaseException, CR_THROW_WITH_SOURCE_INFO
#if CR_COMPILER == CR_COMPILER_GCC
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif // CR_COMPILER == CR_COMPILER_GCC
#include <cppdb/frontend.h> // cppdb::session
#if CR_COMPILER == CR_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // CR_COMPILER == CR_COMPILER_GCC
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/optional.hpp> // boost::optional
#include <cstdint> // std::uint32_t
#include <string> // std::string
#include <vector> // std::vector

namespace cr
{
class TestTypeRepository
    : private boost::noncopyable
{
public:
    static TestType create(std::string str, std::uint32_t num);

    static bool exists(std::uint64_t id);

    static std::uint64_t count();

    static boost::optional<TestType> read(std::uint64_t id);

    static std::vector<TestType> readAll();

    static TestType update(
        std::uint64_t id,
        std::uint32_t num,
        std::string str);

    static void deleteOne(std::uint64_t id);

    static void deleteAll();

private:
    static TestType fetchLastCreated();

    static std::string getStr(cppdb::result &res);

    static std::uint32_t getNum(cppdb::result &res);

    static std::uint64_t getId(cppdb::result &res);

    static cppdb::session &sql;
};
} // namespace cr
#endif // INCG_CR_TEST_TYPE_REPOSITORY_HPP
