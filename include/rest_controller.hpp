#ifndef INCG_CR_REST_CONTROLLER_HPP
#define INCG_CR_REST_CONTROLLER_HPP
#include <boost/noncopyable.hpp> // boost::noncopyable
#include "../include/concurrent.hpp" // cr::Concurrent
#include "../include/launch_async_task.hpp" // cr::launchAsyncTask
#include <ciso646> // not
#include <cstdint> // std::uint16_t
#include <utility> // std::move
#include <string> // std::string
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::literals::chrono::literals::operator""ms

namespace cr
{
/*!
 * \brief Type used to manage a REST-API.
**/
template <typename RestApiImpl>
class RestController
    : private boost::noncopyable
{
public:
    using this_type = RestController;
    using element_type = RestApiImpl;

    /*!
     * \brief Creates a RestController by creating the REST-API to be used
     *        in the Concurrent running on its own thread.
     * \param restbedLogFilepath The path to the restbed log file.
    **/
    RestController(std::string restbedLogFilepath)
        : m_concurrent{ RestApiImpl{ std::move(restbedLogFilepath) } },
          m_wasStopped{ false } /* by default the REST-API was not stopped */
    {
    }

    /*!
     * \brief Destroys a RestController by stopping the REST-API if it
     *        hasn't already been stopped.
    **/
    ~RestController()
    {
        // stop the REST-API if it hasn't already been stopped.
        if (not m_wasStopped) {
            stop();
        }
    }

    /*!
     * \brief stops the REST-API, bringing it offline.
     * \return A reference to this object.
    **/
    this_type &stop()
    {
        // schedule the REST-API to be stopped by the Concurrent.
        // should happen immediately as the thread that the Concurrent owns
        // should really just wait in the ThreadSafeQueue used.
        auto future = m_concurrent([](RestApiImpl &restApiImpl) {
            restApiImpl.stop();
        });

        // wait for the scheduled task to be completed.
        // should always return immediately.
        future.wait();
        m_wasStopped = true; // The REST-API was stopped manually.
        return *this;
    }

    /*!
     * \brief Starts the underlying REST-API, bringing it online.
     * \param port The port to run the REST-API on.
     * \return A future to the REST-API task that is running in its own thread.
     *         Joining that thread by calling .get() or .wait() on the future
     *         returned will block forever, to shut down the REST-API, call
     *         .stop() on this RestController.
     *         Note that the future returned will call .get() implicitly
     *         in its destructor (if .get() hasn't already been called)
     *         as the future returned is created by std::async.
    **/
    std::future<void> start(std::uint16_t port)
    {
        using namespace std::literals::chrono_literals; // bring chrono literals into scope.

        // Schedule a task to be run on the thread owned by the Concurrent.
        // That task will be executed immediately.
        // That task launches another thread, which will run the REST-API
        // forever. Only that thread shall access the REST-API.
        // The Concurrent shall only be used to schedule tasks running
        // on its thread that stop the REST-API.
        std::future<std::future<void>> launchTaskFuture
            = m_concurrent([port](RestApiImpl &restApiImpl) {
                // launch another thread that runs the REST-API forever.
                // The future returned here is used by the Concurrent to
                // set the promise associated with the future returned
                // by the Concurrent's call operator.
                return ::cr::launchAsyncTask(
                    [port, &restApiImpl] {
                        restApiImpl.start(port); // start the REST-API.
                    });
        });

        // get the future to the thread running the REST-API from the
        // future returned by the Concurrent.
        // should return immediately.
        std::future<void> futureToAsyncTask = launchTaskFuture.get();

        // wait a bit to be (somewhat) certain the service is up.
        // otherwise tests may fail.
        std::this_thread::sleep_for(50ms);

        return futureToAsyncTask; // return the future that is a handle to the
                                  // thread running the REST-API.
    }

private:
    Concurrent<RestApiImpl> m_concurrent;
    bool m_wasStopped;
};
} // namespace cr
#endif // INCG_CR_REST_CONTROLLER_HPP
