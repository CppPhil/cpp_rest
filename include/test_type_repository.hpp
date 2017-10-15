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
/*!
 * \brief Repository type for TestType objects.
 *        Defined as a class to make people feel warm and fuzzy.
**/
class TestTypeRepository
    : private boost::noncopyable
{
public:
    /*!
     * \brief Creates a TestType object in the MySQL database.
     * \param str The string to use.
     * \param num The number to use.
     * \return The valid TestType object created,
     *         will have an automaticall generated ID.
     * \throws FailedToFetchFromDatabaseException on error.
    **/
    static TestType create(std::string str, std::uint32_t num);

    /*!
     * \brief Determines whether there is a TestType object in the
     *        database with ID 'id'.
     * \param id The id to use to check for existence of an object of type
     *           TestType.
     * \return true if there is a TestType object with the ID 'id' in the
     *         database, otherwise false.
     * \throws FailedToFetchFromDatabaseException on error.
    **/
    static bool exists(std::uint64_t id);

    /*!
     * \brief Returns the amount of TestType objects in the database.
     * \return The amount of TestType objects in the database.
     * \throws FailedToFetchFromDatabaseException on error.
    **/
    static std::uint64_t count();

    /*!
     * \brief Fetches the TestType object with the ID 'id' from the database.
     * \param id The ID for which to fetch the associated TestType object.
     * \return An optional holding the TestType object with ID 'id' if
     *         there was an object with the ID 'id', or an empty optional
     *         otherwise. The optional can be boolean evaluated using
     *         .operator bool() to check whether it has an object or not.
    **/
    static boost::optional<TestType> read(std::uint64_t id);

    /*!
     * \brief Reads all TestType objects currently stored in the database.
     * \return A vector of all the TestType objects currently in the database.
     * \note Will return an empty vector if there are no TestType objects
     *       in the database.
    **/
    static std::vector<TestType> readAll();

    /*!
     * \brief Modifies a TestType object in the database.
     * \param id The ID of the TestType object that is to be modified.
     * \param num The new number to use.
     * \param str The new string to use.
     * \return The TestType object after having the changes applied to it.
     * \throws FailedToFetchFromDatabaseException if there was no TestType
     *         object with ID 'id' in the database.
    **/
    static TestType update(
        std::uint64_t id,
        std::uint32_t num,
        std::string str);

    /*!
     * \brief Deletes the TestType object with the ID 'id' from the database.
     * \param id The ID of the TestType object that shall be deleted.
    **/
    static void deleteOne(std::uint64_t id);

    /*!
     * \brief Deletes all TestType objects from the database.
    **/
    static void deleteAll();

private:
    /*!
     * \brief Helper function that returns the TestType object that was just
     *        created from the database.
     * \return The TestType object just created.
     * \note Only to be called after just having added a new TestType instance
     *       to the database.
     * \throws FailedToFetchFromDatabaseException on error.
    **/
    static TestType fetchLastCreated();

    /*!
     * \brief Helper function to get the string out of a valid,
     *        already fetched cppdb::result that contains a TestType.
     * \param res The valid, already fetched cppdb::result that contains
     *            a TestType to get the string from.
     * \return The string extracted.
     * \note see the cppdb::result documentation at
     *       http://cppcms.com/sql/cppdb/classcppdb_1_1result.html
    **/
    static std::string getStr(cppdb::result &res);

    /*!
     * \brief Helper function to get the number out of a valid,
     *        already fetched cppdb::result that contains a TestType.
     * \param res The valid, already fetched cppdb::result that contains
     *            a TestType to get the number from.
     * \return The number extracted.
     * \note see the cppdb::result documentation at
     *       http://cppcms.com/sql/cppdb/classcppdb_1_1result.html
    **/
    static std::uint32_t getNum(cppdb::result &res);

    /*!
     * \brief Helper function to get the ID out of a valid,
     *        already fetched cppdb::result that contains a TestType.
     * \param res The valid, already fetched cppdb::result that contains
     *            a TestType to get the ID from.
     * \return The ID extracted.
     * \note see the cppdb::result documentation at
     *       http://cppcms.com/sql/cppdb/classcppdb_1_1result.html
    **/
    static std::uint64_t getId(cppdb::result &res);

    static cppdb::session &sql; /*!< A reference to the cppdb::session of the
                                 *   cr::DataBaseSession singleton
                                **/
};
} // namespace cr
#endif // INCG_CR_TEST_TYPE_REPOSITORY_HPP
