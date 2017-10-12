#include "../../include/namespace_aliases.hpp"
#include "../../include/http_verb.hpp" // cr::HttpVerb
#include "../../include/request.hpp" // cr::sendRequestSync
#include "../../include/http_status_code.hpp" // cr::HttpStatusCode
#include <corvusoft/restbed/settings.hpp> // restbed::Settings
#include <corvusoft/restbed/response.hpp> // restbed::Response
#include <corvusoft/restbed/http.hpp> // restbed::Http::fetch
#include <doctest.h> // TEST_CASE, ...
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <cstddef> // std::size_t
#include <cstdint> // std::uint16_t
#include <string> // std::string, std::literals::string_literals::operator""s
#include <map> // std::multimap

namespace
{
constexpr std::uint16_t port{ 1985U };
constexpr char ipv4Localhost[] = "127.0.0.1";
constexpr char contentType[] = "Content-Type";
constexpr char contentLength[] = "Content-Length";
} // anonymous namespace

#if !defined(CI_APPVEYOR) && !defined(WIN32_DEBUG_MODE)
TEST_CASE("GET_path_param_resource")
{
    using namespace std::literals::string_literals;

    static constexpr char msgToSend[] = "Test";

    const std::shared_ptr<cr::rest::Response> response{
        cr::sendRequestSync(
            ipv4Localhost, port, cr::HttpVerb::GET,
            "/path_param_resource/TEST", // send TEST as the value of the 'name' path parameter
            msgToSend)
    };

    REQUIRE(response != nullptr);

    REQUIRE(response->get_status_code() == cr::HttpStatusCode::OK);

    const std::multimap<std::string, std::string> headers{
        response->get_headers()
    };

    const auto endIt = std::end(headers);

    REQUIRE(headers.find(contentType) != endIt);
    REQUIRE(headers.find(contentType)->second == "text/plain"s);

    REQUIRE(headers.find(contentLength) != endIt);

    REQUIRE_NOTHROW(
        boost::lexical_cast<std::size_t>(headers.find(contentLength)->second));

    const std::size_t length{
        boost::lexical_cast<std::size_t>(headers.find(contentLength)->second)
    };

    // Fetch the response body.
    cr::rest::Http::fetch(length, response);

    const cr::rest::Bytes rawBody{ response->get_body() };
    REQUIRE(rawBody.size() == length);

    // interpret the bytes as string
    const std::string bodyAsString(std::begin(rawBody), std::end(rawBody));

    CHECK(bodyAsString == "You sent: \""s + msgToSend + "\"");
}

TEST_CASE("GET_query_param_resource")
{
    using namespace std::literals::string_literals;

    // no additional headers to send,
    // just the auto-generated ones like Content-Length and Content-Type.
    const std::multimap<std::string, std::string> headersToSend{ };

    // The query parameters to send.
    const std::multimap<std::string, std::string> queryParametersToSend{
        { "queryKey1", "queryValue1" },
        { "queryKey2", "queryValue2" }
    };

    const std::shared_ptr<cr::rest::Response> response{
        cr::sendRequestSync(
            ipv4Localhost, port, cr::HttpVerb::GET,
            "/query_param_resource", "MyMessage",
            headersToSend, queryParametersToSend)
    };

    REQUIRE(response != nullptr);

    REQUIRE(response->get_status_code() == cr::HttpStatusCode::ACCEPTED);

    const std::multimap<std::string, std::string> headers{
        response->get_headers()
    };

    const auto endIt = std::end(headers);

    REQUIRE(headers.find(contentType) != endIt);
    REQUIRE(headers.find(contentType)->second == "text/plain"s);

    REQUIRE(headers.find(contentLength) != endIt);

    REQUIRE_NOTHROW(
        boost::lexical_cast<std::size_t>(headers.find(contentLength)->second));

    const std::size_t length{
        boost::lexical_cast<std::size_t>(headers.find(contentLength)->second)
    };

    // Fetch the response body.
    cr::rest::Http::fetch(length, response);

    const cr::rest::Bytes rawBody{ response->get_body() };
    REQUIRE(rawBody.size() == length);

    // interpret the bytes as string
    const std::string bodyAsString(std::begin(rawBody), std::end(rawBody));

    CHECK(bodyAsString == "query parameters are fun");
}

TEST_CASE("LINK_header_param_resource")
{
    using namespace std::literals::string_literals;

    const std::shared_ptr<cr::rest::Response> response{
        cr::sendRequestSync(
            ipv4Localhost, port, cr::HttpVerb::LINK,
            "/header_param_resource", "blahblahblah",
            { { "Header-Param", "Value" }, // the additional header parameters to send.
              { "Another-Header-Param", "Another value" } })
    };

    REQUIRE(response != nullptr);

    REQUIRE(response->get_status_code()
            == cr::HttpStatusCode::UNAVAILABLE_FOR_LEGAL_REASONS);

    const std::multimap<std::string, std::string> headers{
        response->get_headers()
    };

    const auto endIt = std::end(headers);

    REQUIRE(headers.find(contentType) != endIt);
    REQUIRE(headers.find(contentType)->second == "text/plain"s);

    REQUIRE(headers.find(contentLength) != endIt);

    REQUIRE_NOTHROW(
        boost::lexical_cast<std::size_t>(headers.find(contentLength)->second));

    const std::size_t length{
        boost::lexical_cast<std::size_t>(headers.find(contentLength)->second)
    };

    // Fetch the response body.
    cr::rest::Http::fetch(length, response);

    const cr::rest::Bytes rawBody{ response->get_body() };
    REQUIRE(rawBody.size() == length);

    // interpret the bytes as string
    const std::string bodyAsString(std::begin(rawBody), std::end(rawBody));

    // check the body of the reply.
    CHECK(bodyAsString == "sample text");
}
#endif // !defined(CI_APPVEYOR) && !defined(WIN32_DEBUG_MODE)
