#include "../include/database_session.hpp"
#include <utility> // std::move

namespace cr
{
DataBaseSession::~DataBaseSession() = default;

cppdb::session &DataBaseSession::getInstance()
{
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
