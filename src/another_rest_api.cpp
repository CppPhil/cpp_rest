#include "../include/another_rest_api.hpp"
#include "../include/request.hpp" // cr::getContentLength
#include "../include/response.hpp" // cr::respond
#include "../include/log.hpp" // CR_LOG
#include "../include/unused.hpp" // CR_UNUSED
#include <utility> // std::move
#include <sstream> // std::ostringstream
#include <string> // std::string
#include <map> // std::map, std::multimap

namespace cr
{
AnotherRestApi::AnotherRestApi(std::string restbedLogfilePath)
    : base_type{ this, std::move(restbedLogfilePath), "127.0.0.1" }
{
    // Register the REST resources ...

    registerResource( // A resource with a path parameter
        "/path_param_resource/{name: .*}", // The path parameter is called 'name'.
        HttpVerb::GET,
        &AnotherRestApi::handleGetPathParamResource
    );

    registerResource(
        "/query_param_resource",
        HttpVerb::GET,
        &AnotherRestApi::handleGetQueryParamResource
    );

    registerResource(
        "/header_param_resource",
        HttpVerb::LINK,
        &AnotherRestApi::handleLinkHeaderParamResource
    );
}

AnotherRestApi::AnotherRestApi(this_type &&other)
    : base_type{ std::move(other) }
{
}

AnotherRestApi &AnotherRestApi::operator=(this_type &&other)
{
    base_type::operator=(std::move(other));
    return *this;
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

    // Print the path parameters that were in the request to the log.
    {
        std::ostringstream oss{ };

        for (const auto &pair : pathParameters) {
            const auto &key   = pair.first;
            const auto &value = pair.second;

            oss << "path parameter: " << key << " => " << value << '\n';
        }

        auto s = oss.str();
        s.pop_back();
        CR_LOG(LogLevel::info) << s;
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

void AnotherRestApi::handleGetQueryParamResource(rest::Session &session)
{
    const std::shared_ptr<const rest::Request> request{
        session.get_request()
    };

    if (request == nullptr) {
        CR_LOG(LogLevel::error) << "request was nullptr";
        return;
    }

    const std::multimap<std::string, std::string> queryParameters{
        request->get_query_parameters()
    };

    // Print the query parameters that were in the request to the log.
    {
        std::ostringstream oss{ };

        for (const auto &pair : queryParameters) {
            const auto &key   = pair.first;
            const auto &value = pair.second;

            oss << "query parameter: " << key << " => " << value << '\n';
        }

        auto s = oss.str();
        s.pop_back();
        CR_LOG(LogLevel::info) << s;
    }

    const std::size_t contentLength{ getContentLength(*request) };

    session.fetch(contentLength,
                  [](const std::shared_ptr<rest::Session> session,
                     const rest::Bytes &body) {
        CR_UNUSED(body);
        respond(*session, HttpStatusCode::ACCEPTED,
                "query parameters are fun");
    });
}

void AnotherRestApi::handleLinkHeaderParamResource(rest::Session &session)
{
    const std::shared_ptr<const rest::Request> request{
        session.get_request()
    };

    if (request == nullptr) {
        CR_LOG(LogLevel::error) << "request was nullptr";
        return;
    }

    const std::multimap<std::string, std::string> headers{
        request->get_headers()
    };

    // Print all the headers that were in the request to the log.
    {
        std::ostringstream oss{ };

        for (const auto &pair : headers) {
            const auto &key   = pair.first;
            const auto &value = pair.second;

            oss << "Header: " << key << " => " << value << '\n';
        }

        auto s = oss.str();
        s.pop_back();
        CR_LOG(LogLevel::info) << s;
    }

    const std::size_t contentLength{ getContentLength(*request) };

    session.fetch(contentLength,
                  [](const std::shared_ptr<rest::Session> session,
                     const rest::Bytes &body) {
        CR_UNUSED(body);
        respond(*session, HttpStatusCode::UNAVAILABLE_FOR_LEGAL_REASONS,
                "sample text");
    });
}
} // namespace cr
