#ifndef INCG_CR_CONCURRENT_HPP
#define INCG_CR_CONCURRENT_HPP
#include "thread_safe_queue.hpp" // cr::ThreadSafeQueue
#include "invoke.hpp" // cr::invoke
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <utility> // std::move
#include <memory> // std::make_shared
#include <future> // std::future, std::promise

namespace cr
{
/*!
 * \brief Allows callables to be run on an object managed by a thread.
**/
template <typename Type>
class Concurrent
    : private boost::noncopyable
{
public:
    using this_type = Concurrent;

    /*!
     * \brief Type alias for the template type parameter of 'Concurrent'.
     *        Can be accessed to query the template type paramater
     *        that was used for a given 'Concurrent'.
    **/
    using element_type = Type;

    /*!
     * \brief Starts the underlying thread. The thread will remove and execute
     *        callables stored in the ThreadSafeQueue continuously.
     * \param value The object that the callables passed in the call operator
     *        will operate on.
    **/
    explicit Concurrent(Type value)
        : m_value{ std::move(value) },
          m_q{ },
          m_isDone{ false },
          m_thd{
              [this] {
                  while (not m_isDone) {
                      m_q.pop()();
                  }
              }
          }
    {
    }

    /*!
     * \brief Adds a callable to the ThreadSafeQueue that will set the
     *        is done boolean flag to true. Which will cause the thread to
     *        return. Then the thread is joined.
     *
     * The underlying thread will continue to run the callables still in the
     * ThreadSafeQueue. As soon as the callable that sets is done to true is
     * run the thread will exit its loop. Then the thread calling this
     * destructor joins this instances's underlying thread.
    **/
    ~Concurrent()
    {
        m_q.push([this] {
            m_isDone = true;
        });

        m_thd.join();
    }

    /*!
     * \brief Adds the callable passed in to the queue of things to be
     *        executed by the underlying thread.
     * \param callable The callable that is to be run on the object managed
     *        by the thread by the thread.
     * \return A future that will hold the result of calling the callable
     *         with m_value as soon as that callable has been run, or
     *         an exception, if an exception occurred.
     *         The returned future can be joined on using .get() for instance.
    **/
    template <typename Callable>
    auto operator()(Callable &&callable)
    {
        auto p = std::make_shared<std::promise<decltype(callable(m_value))>>();

        auto ret = p->get_future();

        m_q.push([p, callable, this] {
            try {
                setValue(*p, callable, m_value);
            } catch (...) {
                p->set_exception(std::current_exception());
            }
        });

        return ret;
    }

private:
    // these type aliases are just for gcc
    using Function = std::function<void ()>;
    using concurrent_queue = ThreadSafeQueue<Function>;

    /*!
     * \brief Invokes the callable with ty and sets the result to the promise.
    **/
    template <typename Fut, typename Callable, typename Ty>
    static void setValue(
        std::promise<Fut> &p,
        Callable &callable,
        Ty &ty)
    {
        p.set_value(::cr::invoke(callable, ty));
    }

    /*!
     * \brief Invokes the callable with ty and sets the result to the promise.
     * \note This is the overload that handles the void case, as void is not
     *       a regular type.
    **/
    template <typename Callable, typename Ty>
    static void setValue(
        std::promise<void> &p,
        Callable &callable,
        Ty &ty)
    {
        ::cr::invoke(callable, ty);
        p.set_value();
    }

    Type m_value;
    concurrent_queue m_q;
    bool m_isDone; //!< only accessed from m_thd
    std::thread m_thd;
};
} // namespace cr
#endif // INCG_CR_CONCURRENT_HPP
