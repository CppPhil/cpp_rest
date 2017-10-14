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
class DataBaseSession
    : private boost::noncopyable
{
public:
    using this_type = DataBaseSession;

    ~DataBaseSession();

    static cppdb::session &getInstance();

private:
    explicit DataBaseSession(std::string connectionString);

    std::string m_connectionString;
    cppdb::session m_session;
};
} // namespace cr
#endif // INCG_CR_DATABASE_SESSION_HPP
