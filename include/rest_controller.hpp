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
template <typename RestApiImpl>
class RestController
    : private boost::noncopyable
{
public:
    using this_type = RestController;
    using element_type = RestApiImpl;

    RestController(std::string restbedLogFilepath)
        : m_concurrent{ RestApiImpl{ std::move(restbedLogFilepath) } },
          m_wasStopped{ false }
    {
    }

    this_type &stop()
    {
        auto future = m_concurrent([](RestApiImpl &restApiImpl) {
            restApiImpl.stop();
        });

        future.wait();
        m_wasStopped = true;
        return *this;
    }

    ~RestController()
    {
        if (not m_wasStopped) {
            stop();
        }
    }

    std::future<void> start(std::uint16_t port)
    {
        using namespace std::literals::chrono_literals;

        std::future<std::future<void>> launchTaskFuture
            = m_concurrent([port](RestApiImpl &restApiImpl) {
                return ::cr::launchAsyncTask(
                    [port, &restApiImpl] {
                        restApiImpl.start(port);
                    });
        });

        std::future<void> futureToAsyncTask = launchTaskFuture.get();

        // wait a bit to be (somewhat) certain the service is up.
        std::this_thread::sleep_for(50ms);

        return futureToAsyncTask;
    }

private:
    Concurrent<RestApiImpl> m_concurrent;
    bool m_wasStopped;
};
} // namespace cr
#endif // INCG_CR_REST_CONTROLLER_HPP
