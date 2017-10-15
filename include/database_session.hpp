#ifndef INCG_CR_DATABASE_SESSION_HPP
#define INCG_CR_DATABASE_SESSION_HPP
#include "../include/compiler.hpp" // CR_COMPILER, CR_COMPILER_GCC
#if CR_COMPILER == CR_COMPILER_GCC
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif // CR_COMPILER == CR_COMPILER_GCC
#include <cppdb/frontend.h> // cppdb::session
#if CR_COMPILER == CR_COMPILER_GCC
#   pragma GCC diagnostic pop
#endif // CR_COMPILER == CR_COMPILER_GCC
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <string> // std::string

namespace cr
{
/*!
 * \brief DataBaseSession singleton type.
 *        Used by the repository types.
**/
class DataBaseSession
    : private boost::noncopyable
{
public:
    using this_type = DataBaseSession;

    /*!
     * \brief Destroys a DataBaseSession object.
    **/
    ~DataBaseSession();

    /*!
     * \brief Returns a reference to the cppdb::session object owned by
     *        the DataBaseSession singleton object.
     * \return A reference to the cppdb::session object.
    **/
    static cppdb::session &getInstance();

private:
    /*!
     * \brief Creates a DataBaseSession object from a MySQL connection string.
     * \param connectionString The MySQL connection string.
    **/
    explicit DataBaseSession(std::string connectionString);

    std::string m_connectionString; /*!< The MySQL connection string */
    cppdb::session m_session; /*!< The underlying database session */
};
} // namespace cr
#endif // INCG_CR_DATABASE_SESSION_HPP
