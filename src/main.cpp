#include "../include/example_rest_api.hpp"
#include "../include/unused.hpp" // CR_UNUSED
#include "../include/except.hpp" // CR_THROW_WITH_SOURCE_INFO
#include <cstddef> // std::size_t
#include <cstring> // std::strlen
#include <iostream> // std::cerr
#include <stdexcept> // std::runtime_error
#include <exception> // std::terminate
#include <string> // std::string
#include <iterator> // std::make_reverse_iterator
#include <algorithm> // std::find_if

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
        CR_THROW_WITH_SOURCE_INFO(std::runtime_error,
                                  R"(argv[0] had no "\" or "/"!)");
    }

    return std::string(begin, it.base());
}
} // anonymous namespace

int main(int argc, char *argv[])
{
    static constexpr int applicationIdx = 0;

    CR_UNUSED(argc);

    const std::string exampleRestApiRestbedLogFilePath{
        getApplicationRootPath(argv[applicationIdx])
        + "example_rest_api_restbed.log"
    };

    // Create the example REST API and have this thread run it.

    cr::ExampleRestApi exampleRestApi{ exampleRestApiRestbedLogFilePath };
    static constexpr std::uint16_t port = 1984U;
    exampleRestApi.start(port);
}
