#include "../include/example_rest_api.hpp"
#include "../include/unused.hpp" // CR_UNUSED
#include <cstddef> // std::size_t
#include <cstring> // std::strlen
#include <iostream> // std::cerr
#include <exception> // std::terminate
#include <string> // std::string
#include <iterator> // std::make_reverse_iterator
#include <algorithm> // std::find_if

int main(int argc, char *argv[])
{
    static constexpr int applicationIdx = 0;

    CR_UNUSED(argc);

    const std::size_t strLen{ std::strlen(argv[applicationIdx]) };
    const char * const begin{ argv[applicationIdx] };
    const char * const end{ begin + strLen };
    const auto rbegin = std::make_reverse_iterator(end);
    const auto rend = std::make_reverse_iterator(begin);
    const auto it = std::find_if(rbegin, rend,
                                 [](char c) {
        return (c == '\\') || (c == '/');
    });

    if (it == rend) {
        std::cerr << R"(argv[0] had no "\" or "/"!\n)";
        std::terminate();
    }

    const std::string exampleRestApiRestbedLogFilePath{
        std::string(begin, it.base()) + "example_rest_api_restbed.log"
    };

    // Create the example REST API and have this thread run it.

    cr::ExampleRestApi exampleRestApi{ exampleRestApiRestbedLogFilePath };
    static constexpr std::uint16_t port = 1984U;
    exampleRestApi.start(port);
}
