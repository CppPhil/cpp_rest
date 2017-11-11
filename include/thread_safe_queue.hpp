#ifndef INCG_CR_THREAD_SAFE_QUEUE_HPP
#define INCG_CR_THREAD_SAFE_QUEUE_HPP
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <ciso646> // not
#include <queue> // std::queue
#include <mutex> // std::mutex, ...
#include <condition_variable> // std::condition_variable

namespace cr
{
/*!
 * \brief Allows the user to push elements to the back of the ThreadSafeQueue
 *        and pop elements from the front.
 *
 * This class can be accessed from multiple threads at the same time.
**/
template <typename ValueType>
class ThreadSafeQueue
    : private boost::noncopyable
{
public:
    using this_type = ThreadSafeQueue;
    using value_type = ValueType;
    using container_type = std::queue<value_type>;
    using size_type = typename container_type::size_type;

    /*!
     * \brief Creates a ThreadSafeQueue.
     *        The ThreadSafeQueue will start out empty.
    **/
    ThreadSafeQueue() noexcept
        : m_cont{ },
          m_mutex{ },
          m_cvHasElements{ }
    {
    }

    /*!
     * \brief Removes the first element and returns it.
     * \return The element that used to be at the front of the queue.
     *
     * If the queue is currently empty the calling thread will be put to sleep
     * until the queue is no longer empty.
    **/
    value_type pop()
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cvHasElements.wait(lock, [this] {
            return not m_cont.empty();
        });
        auto retMe = m_cont.front();
        m_cont.pop();
        return retMe;
    }

    /*!
     * \brief Pushes the object passed into the parameter to the back of the
     *        queue.
     * \param data The object to push the the back of the queue.
     * \return A reference to this object.
     *
     * Will notify threads waiting for the queue to no longer be empty that
     * the queue is no longer empty.
    **/
    this_type &push(const value_type &data)
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cont.push(data);
        m_cvHasElements.notify_all();
        return *this;
    }

    /*!
     * \brief Pushes the rvalue passed to the back of the queue.
     * \param data The rvalue to add to the back of the queue
     * \return A reference to this object.
     *
     * Will notify threads waiting for the queue to no longer be empty that
     * the queue is no longer empty.
    **/
    this_type &push(value_type &&data)
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        m_cont.push(std::move(data));
        m_cvHasElements.notify_all();
        return *this;
    }

    /*!
     * \brief Queries the queue as to whether or not it is empty.
     * \return true if the queue is empty; false otherwise.
    **/
    bool empty() const noexcept
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        return m_cont.empty();
    }

    /*!
     * \brief Queries the queue's size.
     * \return The size of the queue.
    **/
    size_type size() const noexcept
    {
        std::unique_lock<std::mutex> lock{ m_mutex };
        return m_cont.size();
    }

private:
    container_type m_cont;
    mutable std::mutex m_mutex;
    std::condition_variable m_cvHasElements;
};
} // namespace cr
#endif // INCG_CR_THREAD_SAFE_QUEUE_HPP
