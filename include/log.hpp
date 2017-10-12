/*!
 * \file log.hpp
 * \brief Exports the CR_LOG macro that is to be used to write to
 *        the application's log file.
**/
#ifndef INCG_CRS_LOG_HPP
#define INCG_CRS_LOG_HPP
#include "../include/except.hpp" // CR_THROW_IF_NULL, cr::NullPointerException
#include <boost/current_function.hpp> // BOOST_CURRENT_FUNCTION
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <mutex> // std::mutex
#include <ostream> // std::ostream
#include <fstream> // std::ofstream
#include <string> // std::string
#include <utility> // std::forward

/*!
 * \def CR_LOG(loglevel)
 * \brief Macro to write to the application's log file using operator<<.
 *        The parameter must be an enumerator of the cr::LogLevel scoped enum.
 * \example CR_LOG(LogLevel::Error) << "An error occurred";
**/

#define CR_LOG(loglevel) \
    ::cr::Log::getInstance().log(loglevel) \
        << "\nFile:    " << __FILE__ \
        << "\nFunction " << BOOST_CURRENT_FUNCTION \
        << "\nLine:    " << __LINE__ \
        << "\nMessage: \n"

namespace cr
{
/*!
 * \brief Scoped enum type of the different enumerators representing the
 *        different log levels that may be used as arguments to the
 *        CR_LOG macro.
**/
enum class LogLevel
{
    debug,
    info,
    warning,
    error,
    critical,
    fatal
};

class Log; // forward declaration of type Log, needed by WriteToLogProxy.

/*!
 * \brief Type which serves as the result type of the expression that CR_LOG
 *        expands to. This type is used to write to the application's log
 *        file through CR_LOG. Locks the mutex for the Log singleton
 *        in the constructor and unlocks it in the destructor.
 *        Used to synchronize access to the shared log file handle
 *        by having an instance of this type lock the shared mutex by creating
 *        it from the expression that CR_LOG expands to and having it unlock
 *        the mutex at the end of the expression.
**/
class WriteToLogProxy
    : private boost::noncopyable
{
public:
    using this_type = WriteToLogProxy;

    /*!
     * \brief Creates an object of type WriteToLogProxy.
     *        Locks the mutex of the Log passed into the parameter.
     * \param log A reference to the Log singleton object.
     * \note This constructor is called by Log::log.
    **/
    explicit WriteToLogProxy(Log &log);

    /*!
     * \brief Move constructs an object of type WriteToLogProxy.
     *        Takes the pointers from 'other' und nulls out 'other''s pointers.
     * \param other The object to move construct from.
    **/
    WriteToLogProxy(this_type &&other);

    /*!
     * \brief Destroys a WriteToLogProxy.
     *        Writes two new line characters to the log file, flushes
     *        the log file causing it to be written out to the harddrive
     *        and unlocks the Log's mutex if this WriteToLogProxy is not
     *        a moved-from object.
    **/
    ~WriteToLogProxy();

    /*!
     * \brief Prints a printable object to the log file.
     * \param proxy A reference to the current WriteToLogProxy prvalue
     *              that exists for the duration of the CR_LOG expression.
     * \param ty The object to print.
     * \throws cr::NullPointerException if the WriteToLogProxy is a moved-from
     *         object.
    **/
    template <typename Ty>
    friend const WriteToLogProxy &operator<<(
        const WriteToLogProxy &proxy,
        Ty &&ty)
    {
        // the pointer can't be nullptr!
        CR_THROW_IF_NULL(proxy.m_ofstream);

        // print it.
        (*(proxy.m_ofstream)) << std::forward<Ty>(ty);
        return proxy;
    }

private:
    std::ofstream *m_ofstream; /*!< Pointer to the ofstream of the Log singleton */
    std::mutex *m_mu; /*!< Pointer of the shared mutex inside of the Log singleton */
};

/*!
 * \brief The underlying Log type used by CR_LOG.
**/
class Log
    : private boost::noncopyable
{
public:
    using this_type = Log;

    friend WriteToLogProxy; // befriend WriteToLogProxy so it can fetch its pointers.

    /*!
     * \brief Returns a reference to the Log singleton object.
     * \return A reference to the Log singleton object.
    **/
    static this_type &getInstance();

    /*!
     * \brief Function called by the CR_LOG macro.
     *        Creates a WriteToLogProxy object, writes the text for the
     *        given LogLevel to the log file and then returns the WriteToLogProxy.
     * \param logLevel The LogLevel to use.
     * \return The WriteToLogProxy object created.
    **/
    WriteToLogProxy log(LogLevel logLevel);

private:
    /*!
     * \brief Constructor of the Log type.
     *        Creates an object of type Log.
     *        Enables exceptions on the underlying filehandle to the log file.
     * \param logfilePath The path of the log file to write to.
     * \throws std::ios_base::failure if the ofstream was not in a good state
     *         after having tried to open the file (Most likely the file
     *         could not be created / opened).
    **/
    explicit Log(std::string logfilePath);

    std::string m_logfilePath; /*!< The string passed into the constructor */
    std::ofstream m_ofstream; /*!< The underlying handle to the log file */
    std::mutex m_mu; /*!< The shared mutex used by the WriteToLogProxy objects */
};
} // namespace cr
#endif // INCG_CRS_LOG_HPP
