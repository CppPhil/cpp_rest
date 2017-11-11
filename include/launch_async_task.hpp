#ifndef INCG_CR_LAUNCH_ASYNC_TASK_HPP
#define INCG_CR_LAUNCH_ASYNC_TASK_HPP
#include <utility> // std::forward
#include <future> // std::async

namespace cr
{
/*!
 * \brief Wrapper function template to call std::async with std::launch::async.
 *        Spawns a new thread and runs the invocation of 'callable' with 'args'
 *        in the new thread.
 * \param callable The callable to be invoked on the new thread.
 * \param args The arguments to pass to 'callable'.
 * \return A std::future to the result of invoking 'callable' with 'args'.
**/
template <typename Callable, typename ...Args>
auto launchAsyncTask(Callable &&callable, Args &&...args) -> decltype(auto)
{
    return std::async(
        std::launch::async,
        std::forward<Callable>(callable),
        std::forward<Args>(args)...
    );
}
} // naempspace cr
#endif // INCG_CR_LAUNCH_ASYNC_TASK_HPP
