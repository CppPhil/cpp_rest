#include "../include/database_session.hpp"
#include <utility> // std::move

namespace cr
{
DataBaseSession::~DataBaseSession() = default;

cppdb::session &DataBaseSession::getInstance()
{
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
