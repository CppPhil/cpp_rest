#include "../include/example_rest_api.hpp"

int main()
{
    // Create the example REST API and have this thread run it.

    cr::ExampleRestApi exampleRestApi{ };
    static constexpr std::uint16_t port = 1984U;
    exampleRestApi.start(port);
}
