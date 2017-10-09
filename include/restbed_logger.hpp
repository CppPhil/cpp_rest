#ifndef INCG_CR_RESTBED_LOGGER_HPP
#define INCG_CR_RESTBED_LOGGER_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/except.hpp" // cr::FailedToCreateRestbedLogger
#include <restbed> // restbed::Logger, restbed::Settings
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstdarg> // std::va_list
#include <cstdio> // std::FILE
#include <memory> // std::shared_ptr

namespace cr
{
/*!
 * \brief Custom restbed Logger type.
 *        To be registered with a restbed::Service.
**/
class RestbedLogger
    : public rest::Logger
{
public:
    using this_type = RestbedLogger;
    using base_type = rest::Logger;

    /*!
     * \brief Creates a RestbedLogger object.
     * \param logfilePath The file path of the file to have the log write to.
     * \throws cr::FailedToCreateRestbedLogger if the file 'logfilePath'
     *         could not be opened for writing.
    **/
    explicit RestbedLogger(boost::string_ref logfilePath);

    /*!
     * \brief Destroys a RestbedLogger object.
     *        Closes the underlying file.
     * \warning May call std::terminate if the underlying file could not
     *          be closed.
    **/
    ~RestbedLogger();

    /*!
     * \brief Does nothing.
    **/
    virtual void stop() override;

    /*!
     * \brief Does nothing.
     * \param settings Unused parameter.
    **/
    virtual void start(
        const std::shared_ptr<const rest::Settings> &settings) override;

    /*!
     * \brief Writes to the log file.
     * \param level The log level.
     * \param format A null-terminated printf style format string.
    **/
    virtual void log(const Level level, const char *format, ...) override;

    /*!
     * \brief Conditionally writes to the log file.
     * \param expression If true, will write to the log file. Otherwise
     *                   this non-static member function does nothing.
     * \param level The log level.
     * \param format A null-terminated printf style format string.
    **/
    virtual void log_if(
        bool expression,
        const Level level,
        const char *format,
        ...) override;

private:
    /*!
     * \brief Converts a Level enumerator to a null-terminated byte character
     *        string.
     * \param level The enumerator to convert.
     * \return The resulting C-style string.
    **/
    static const char *loglevelAsString(Level level);

    /*!
     * \brief Implementation function for log and log_if taking a va_list.
     * \param level The log level.
     * \param format The null-terminated printf style format string.
     * \param args The va_list to use.
    **/
    void vlog(Level level, const char *format, std::va_list args);

    std::FILE *m_file; /*!< The underlying file */
};
} // namespace cr
#endif // INCG_CR_RESTBED_LOGGER_HPP
