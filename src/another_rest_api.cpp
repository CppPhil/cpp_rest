#include "../include/another_rest_api.hpp"
#include "../include/request.hpp" // cr::getContentLength
#include "../include/response.hpp" // cr::respond
#include "../include/log.hpp" // CR_LOG
#include <utility> // std::move
#include <string> // std::string
#include <map> // std::map

namespace cr
{
AnotherRestApi::AnotherRestApi(std::string restbedLogfilePath)
    : base_type{ this, std::move(restbedLogfilePath), "127.0.0.1" }
{
    // Register the REST resources ...

    registerResource(
        "/path_param_resource/{name: .*}",
        HttpVerb::GET,
        &AnotherRestApi::handleGetPathParamResource
    );
}

AnotherRestApi::~AnotherRestApi() = default;

AnotherRestApi &AnotherRestApi::start(std::uint16_t port)
{
    startRestApi(port);
    return *this;
}

void AnotherRestApi::handleGetPathParamResource(rest::Session &session)
{
    const std::shared_ptr<const rest::Request> request{
        session.get_request()
    };

    if (request == nullptr) {
        CR_LOG(LogLevel::error) << "request was nullptr";
        return;
    }

    const std::map<std::string, std::string> pathParameters{
        request->get_path_parameters()
    };

    for (const auto &pair : pathParameters) {
        const auto &key   = pair.first;
        const auto &value = pair.second;

        CR_LOG(LogLevel::info)
            << "path parameter: " << key << " => " << value;
    }

    const std::size_t contentLength{ getContentLength(*request) };

    session.fetch(contentLength,
                  [](const std::shared_ptr<rest::Session> session,
                     const rest::Bytes &body) {
        const std::string s(std::begin(body), std::end(body));
        respond(*session, HttpStatusCode::OK,
                "You sent: \"" + s + "\"");
    });
}
} // namespace cr
