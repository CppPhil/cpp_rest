#include "../include/restbed_logger.hpp"
#include <boost/current_function.hpp> // BOOST_CURRENT_FUNCTION
#include <ciso646> // not
#include <cstdarg> // std::va_list, va_start, va_end
#include <exception> // std::terminate
#include <string> // std::string, std::literals::string_literals::operator""s
#include <iostream> // std::cerr

namespace cr
{
RestbedLogger::RestbedLogger(boost::string_ref logfilePath)
    : m_file{ std::fopen(logfilePath.data(), "w") }
{
    using namespace std::literals::string_literals;

    if (m_file == nullptr) {
        CR_THROW_WITH_SOURCE_INFO(FailedToCreateRestbedLogger,
                                  "Failed to open file \""s
                                  + logfilePath.data()
                                  + "\"");
    }
}

RestbedLogger::~RestbedLogger()
{
    if (std::fclose(m_file) == EOF) {
        std::cerr << BOOST_CURRENT_FUNCTION << ": failed to close file\n";
        std::terminate();
    }
}

void RestbedLogger::stop()
{
}

void RestbedLogger::start(const std::shared_ptr<const rest::Settings> &settings)
{
    static_cast<void>(settings);
}

void RestbedLogger::log(const Level level, const char *format, ...)
{
    std::va_list args{ };
    va_start(args, format);
    vlog(level, format, args);
    va_end(args);
}

void RestbedLogger::log_if(bool expression,
                           const Level level,
                           const char *format, ...)
{
    if (not expression) {
        return;
    }

    std::va_list args{ };
    va_start(args, format);
    vlog(level, format, args);
    va_end(args);
}

const char *RestbedLogger::loglevelAsString(Level level)
{
    switch (level) {
    case Level::INFO:
        return "INFO";
    case Level::DEBUG:
        return "DEBUG";
    case Level::FATAL:
        return "FATAL";
    case Level::ERROR:
        return "ERROR";
    case Level::WARNING:
        return "WARNING";
    case Level::SECURITY:
        return "SECURITY";
    default:
        break;
    }

    return "INVALID LEVEL!";
}

void RestbedLogger::vlog(Level level,
                         const char *format,
                         std::va_list args)
{
    std::fprintf(m_file, "%s:", loglevelAsString(level));
    std::vfprintf(m_file, format, args);
    std::fprintf(m_file, "\n");
}
} // namespace cr
