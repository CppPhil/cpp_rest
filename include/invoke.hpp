#ifndef INCG_CR_INVOKE_HPP
#define INCG_CR_INVOKE_HPP
#include <type_traits> // std::true_type, std::false_type, std::decay_t, ...
#include <functional> // std::mem_fn
#include <utility> // std::forward

namespace cr
{
namespace detail
{
/*!
 * \brief Implementation function template of invoke.
 *        Not to be used directly.
**/
template <typename Callable, typename ...Args>
auto invokeImpl(
    std::true_type,
    Callable &&callable,
    Args &&...args)
    noexcept(noexcept(std::mem_fn(callable)(std::forward<Args>(args) ...)))
    -> decltype(auto)
{
    return std::mem_fn(callable)(std::forward<Args>(args) ...);
}

/*!
 * \brief Implementation function template of invoke.
 *        Not to be used directly.
**/
template <typename Callable, typename ...Args>
auto invokeImpl(
    std::false_type,
    Callable &&callable,
    Args &&...args)
    noexcept(noexcept(std::forward<Callable>(callable)(std::forward<Args>(args) ...)))
    -> decltype(auto)
{
    return std::forward<Callable>(callable)(std::forward<Args>(args) ...);
}
} // namespace detail

/*!
 * \brief Calls 'callable' with 'args'.
 * \param callable The callable object to be invoked.
 * \param args The arguments to pass to 'callable'.
 * \return The result of invoking 'callable' with 'args'.
 *
 * Calls the callable 'callable' with 'args'.
 * Offers a uniform interface to invoke free functions,
 * function objects (including lambdas), member function pointers,
 * as well as access non-static data members through member object pointers.
**/
template <typename Callable, typename ...Args>
auto invoke(Callable &&callable, Args &&...args)
    noexcept(noexcept(::cr::detail::invokeImpl(typename std::is_member_pointer<std::decay_t<Callable>>::type{ },
                                               std::forward<Callable>(callable), std::forward<Args>(args) ...)))
    -> decltype(auto)
{
    return ::cr::detail::invokeImpl(typename std::is_member_pointer<std::decay_t<Callable>>::type{ },
                                    std::forward<Callable>(callable), std::forward<Args>(args) ...);
}
} // namespace cr
#endif // INCG_CR_INVOKE_HPP
