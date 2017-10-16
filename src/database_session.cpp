#include "../include/database_session.hpp"
#include "../include/os.hpp" // CR_OS, CR_OS_WINDOWS
#include <cppdb/backend.h> // cppdb::backend::connection
#include <cppdb/driver_manager.h> // cppdb::driver_manager
#include <utility> // std::move
#if CR_OS == CR_OS_WINDOWS
#   include <mutex> // std::call_once, std::once_flag
#endif // CR_OS == CR_OS_WINDOWS

#if CR_OS == CR_OS_WINDOWS
extern "C"
{
cppdb::backend::connection *cppdb_mysql_get_connection(
    const cppdb::connection_info &);
} // extern "C"
#endif // CR_OS == CR_OS_WINDOWS

namespace cr
{
DataBaseSession::~DataBaseSession() = default;

cppdb::session &DataBaseSession::getInstance()
{
#if CR_OS == CR_OS_WINDOWS
    static std::once_flag onceFlag{ };

    std::call_once(
        onceFlag,
        [] {
            cppdb::driver_manager::instance().install_driver(
                "mysql",
                new cppdb::backend::static_driver{
                    &cppdb_mysql_get_connection
                }
            );
        }
    );
#endif // CR_OS == CR_OS_WINDOWS

    // For documentation of this MySQL connection string, see:
    // http://cppcms.com/sql/cppdb/classcppdb_1_1session.html#a7ae75affbf1b2e809250a6e2ff36bf2c
    static constexpr char connectionString[]
        = "mysql:user=testuser;password=password;database=testdb;";

    static DataBaseSession dataBaseSession{ connectionString };
    return dataBaseSession.m_session;
}

DataBaseSession::DataBaseSession(std::string connectionString)
    : m_connectionString{ std::move(connectionString) },
      m_session{ m_connectionString }
{
}
} // namespace cr
