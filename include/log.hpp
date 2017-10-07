#ifndef INCG_CRS_LOG_HPP
#define INCG_CRS_LOG_HPP
#include "../include/except.hpp" // CR_THROW_IF_NULL
#include <boost/current_function.hpp> // BOOST_CURRENT_FUNCTION
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <mutex> // std::mutex
#include <ostream> // std::ostream
#include <fstream> // std::ofstream
#include <string> // std::string
#include <utility> // std::forward

#define CR_LOG(loglevel) \
    ::cr::Log::getInstance().log(loglevel) \
        << "\nFile:    " << __FILE__ \
        << "\nFunction " << BOOST_CURRENT_FUNCTION \
        << "\nLine:    " << __LINE__ \
        << "\nMessage: "

namespace cr
{
enum class LogLevel
{
    debug,
    info,
    warning,
    error,
    critical,
    fatal
};

class Log;

class WriteToLogProxy
    : private boost::noncopyable
{
public:
    using this_type = WriteToLogProxy;

    explicit WriteToLogProxy(Log &log);

    WriteToLogProxy(this_type &&other);

    ~WriteToLogProxy();

    template <typename Ty>
    friend const WriteToLogProxy &operator<<(const WriteToLogProxy &proxy,
                                             Ty &&ty)
    {
        CR_THROW_IF_NULL(proxy.m_ofstream);

        (*(proxy.m_ofstream)) << std::forward<Ty>(ty);
        return proxy;
    }

private:
    std::ofstream *m_ofstream;
    std::mutex *m_mu;
};

class Log
    : private boost::noncopyable
{
public:
    using this_type = Log;

    friend WriteToLogProxy;

    static this_type &getInstance();

    WriteToLogProxy log(LogLevel logLevel);

private:
    explicit Log(std::string logfilePath);

    std::string m_logfilePath;
    std::ofstream m_ofstream;
    std::mutex m_mu;
};
} // namespace cr
#endif // INCG_CRS_LOG_HPP
