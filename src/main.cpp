#include "../include/example_rest_api.hpp" // cr::ExampleRestApi
#include "../include/another_rest_api.hpp" // cr::AnotherRestApi
#include "../include/unused.hpp" // CR_UNUSED
#include "../include/except.hpp" // CR_THROW_WITH_SOURCE_INFO
#include "../include/black_board_info.hpp" // cr::BlackBoardInfo
#include "../include/rest_controller.hpp" // cr::RestController
#include <cstdlib> // EXIT_FAILURE
#include <iostream> // std::cerr, std::cout
#include <string> // std::string

int main()
{
    try {
        const std::string exampleRestApiRestbedLogFilePath{
            "./example_rest_api_restbed.log"
        };

        const std::string anotherRestApiRestbedLogFilePath{
            "./another_rest_api_restbed.log"
        };

        const cr::BlackBoardInfo blackBoardInfo{ cr::BlackBoardInfo::create() };
        std::cout << blackBoardInfo << '\n';

        cr::RestController<cr::ExampleRestApi> exampleRestApi{
            exampleRestApiRestbedLogFilePath };
        static constexpr std::uint16_t exampleRestApiPort{ 1984U };

        cr::RestController<cr::AnotherRestApi> anotherRestApi{
            anotherRestApiRestbedLogFilePath
        };
        static constexpr std::uint16_t anotherRestApiPort{ 1985U };

        auto exampleRestApiFuture = exampleRestApi.start(exampleRestApiPort);
        auto anotherRestApiFuture = anotherRestApi.start(anotherRestApiPort);

        exampleRestApiFuture.wait();
        anotherRestApiFuture.wait();

        exampleRestApi.stop();
        anotherRestApi.stop();

    } catch (const std::exception &ex) {
        std::cerr << "main(): caught exception: " << ex.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "main(): caught unknown exception!\n";
        return EXIT_FAILURE;
    }
}
