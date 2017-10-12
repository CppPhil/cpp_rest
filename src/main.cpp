#include "../include/example_rest_api.hpp" // cr::ExampleRestApi
#include "../include/another_rest_api.hpp" // cr::AnotherRestApi
#include "../include/unused.hpp" // CR_UNUSED
#include "../include/except.hpp" // CR_THROW_WITH_SOURCE_INFO
#include <cstddef> // std::size_t
#include <cstring> // std::strlen
#include <stdexcept> // std::runtime_error
#include <exception> // std::terminate
#include <string> // std::string
#include <utility> // std::forward
#include <iterator> // std::make_reverse_iterator
#include <algorithm> // std::find_if
#include <future> // std::async

namespace
{
/*!
 * \brief Module local function to get the path to the directory containing
 *        this application's executable.
 * \param argv0 The argv[0] null-terminated byte character string.
 * \return The path to the directory containing this application's executable.
 * \throws std::runtime_error if 'argv0' was invalid.
**/
std::string getApplicationRootPath(const char *argv0)
{
    const std::size_t strLen{ std::strlen(argv0) };
    const char * const begin{ argv0 };
    const char * const end{ begin + strLen };
    const auto rbegin = std::make_reverse_iterator(end);
    const auto rend = std::make_reverse_iterator(begin);
    const auto it = std::find_if(rbegin, rend,
                                 [](char c) {
        return (c == '\\') || (c == '/');
    });

    if (it == rend) {
        CR_THROW_WITH_SOURCE_INFO(
            std::runtime_error,
            R"(argv[0] had no "\" or "/"!)");
    }

    return std::string(begin, it.base());
}

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
} // anonymous namespace

int main(int argc, char *argv[])
{
    static constexpr int applicationIdx = 0;

    CR_UNUSED(argc);

    const std::string applicationRootPath{
        getApplicationRootPath(argv[applicationIdx])
    };

    const std::string exampleRestApiRestbedLogFilePath{
        applicationRootPath
        + "example_rest_api_restbed.log"
    };

    const std::string anotherRestApiRestbedLogFilePath{
        applicationRootPath
        + "another_rest_api_restbed.log"
    };

    std::future<void> f1{ launchAsyncTask(
        [&exampleRestApiRestbedLogFilePath] {
            cr::ExampleRestApi exampleRestApi{ exampleRestApiRestbedLogFilePath };
            static constexpr std::uint16_t port{ 1984U };
            exampleRestApi.start(port);
    }) };

    std::future<void> f2{ launchAsyncTask(
        [&anotherRestApiRestbedLogFilePath] {
            cr::AnotherRestApi anotherRestApi{ anotherRestApiRestbedLogFilePath };
            static constexpr std::uint16_t port{ 1985U };
            anotherRestApi.start(port);
    }) };
}
