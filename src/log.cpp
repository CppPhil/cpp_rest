#include "../include/log.hpp"
#include <ciso646> // not

namespace cr
{
namespace
{
constexpr char logfilePath[] = "cpp_rest.log";

const char *loglevelAsStr(LogLevel logLevel)
{
    switch (logLevel) {
    case LogLevel::debug:
        return "[DEBUG] ";
    case LogLevel::error:
        return "[ERROR] ";
    case LogLevel::critical:
        return "[CRITICAL] ";
    case LogLevel::info:
        return "[INFO] ";
    case LogLevel::warning:
        return "[WARNING] ";
    case LogLevel::fatal:
        // FALLTHROUGH
    default:
        break;
    }

    return "[FATAL] ";
}
} // anonymous namespace

WriteToLogProxy::WriteToLogProxy(Log &log)
    : m_ofstream{ &(log.m_ofstream) },
      m_mu{ &(log.m_mu) }
{
    m_mu->lock();
}

WriteToLogProxy::WriteToLogProxy(this_type &&other)
    : m_ofstream{ nullptr },
      m_mu{ nullptr }
{
    std::swap(m_ofstream, other.m_ofstream);
    std::swap(m_mu, other.m_mu);
}

WriteToLogProxy::~WriteToLogProxy()
{
    if (m_ofstream != nullptr) {
        (*m_ofstream) << "\n\n" << std::flush;
    }

    if (m_mu == nullptr) {
        return;
    }

    m_mu->unlock();
}

Log &Log::getInstance()
{
    static Log log{ logfilePath };
    return log;
}

WriteToLogProxy Log::log(LogLevel logLevel)
{
    WriteToLogProxy proxy{ *this };
    proxy << loglevelAsStr(logLevel);
    return proxy;
}

Log::Log(std::string logfilePath)
    : m_logfilePath{ std::move(logfilePath) },
      m_ofstream{ m_logfilePath },
      m_mu{ }
{
    if (not m_ofstream) {
        throw std::ios_base::failure{
            m_logfilePath + " is not a valid path for the log"
        };
    }

    m_ofstream.exceptions(std::ofstream::failbit | std::ofstream::badbit
                          | std::ofstream::eofbit);
}
} // namespace cr
