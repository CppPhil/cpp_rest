#include "../include/log.hpp"
#include <ciso646> // not

namespace cr
{
namespace
{
/*!
 * \brief The path of the application's log file.
 *        A relative path.
 *        The log file will be created in the directory the executable
 *        is located in.
**/
constexpr char logfilePath[] = "cpp_rest.log";

/*!
 * \brief Module local function to get a C-Style string corresponding to the
 *        LogLevel passed in.
 * \param logLevel The loglevel to get a C-Style string for.
 * \return The null-terminated byte character string corresponding to the
 *         LogLevel passed in.
**/
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
    default: // an invalid value is considered 'fatal'.
        break;
    }

    return "[FATAL] ";
}
} // anonymous namespace

WriteToLogProxy::WriteToLogProxy(Log &log)
    : m_ofstream{ &(log.m_ofstream) }, // fetch the pointers.
      m_mu{ &(log.m_mu) }
{
    m_mu->lock(); // lock the mutex. (It will be unlocked in the dtor.)
}

WriteToLogProxy::WriteToLogProxy(this_type &&other) // move constructor
    : m_ofstream{ nullptr }, // start as nullptr.
      m_mu{ nullptr }
{
    // swap the nullptrs with the ones that other holds.
    std::swap(m_ofstream, other.m_ofstream);
    std::swap(m_mu, other.m_mu);
}

WriteToLogProxy::~WriteToLogProxy()
{
    // if this is not a moved from object put newlines into the log file
    // to end this log entry and flush it to disk.
    if (m_ofstream != nullptr) {
        (*m_ofstream) << "\n\n"
                      << std::flush; // writing the data out to the file like this
                                     // after every log entry is a significant
                                     // performance overhead. This however makes
                                     // debugging much easier as the application
                                     // is designed to effectively run forever
                                     // waiting for requests to come in.
    }

    // if this is a moved from object -> return. There is no mutex to unlock.
    if (m_mu == nullptr) {
        return;
    }

    // Unlock the mutex as this object goes out of scope.
    // (At the end of the expression formed with CR_LOG)
    m_mu->unlock();
}

Log &Log::getInstance()
{
    // Create the Log with static storage duration
    static Log log{ logfilePath };

    // return a reference to the log instance.
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
    // if the ofstream is not ok -> throw.
    if (not m_ofstream) {
        throw std::ios_base::failure{
            m_logfilePath + " is not a valid path for the log"
        };
    }

    // Enable exceptions for the filestream.
    m_ofstream.exceptions(std::ofstream::failbit
                          | std::ofstream::badbit
                          | std::ofstream::eofbit);
}
} // namespace cr
