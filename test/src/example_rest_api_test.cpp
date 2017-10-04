#include "../../include/namespace_aliases.hpp"
#include "../../include/http_verb.hpp" // cr::HttpVerb
#include "../../include/request.hpp" // cr::sendRequestSync
#include "../../include/http_status_code.hpp" // cr::HttpStatusCode
#include "../../include/json.hpp" // cr::parseJson, cr::fromJson
#include "../../include/example_type.hpp" // cr::ExampleType
#include <corvusoft/restbed/settings.hpp> // restbed::Settings
#include <corvusoft/restbed/response.hpp> // restbed::Response
#include <corvusoft/restbed/http.hpp> // restbed::Http::fetch
#include <doctest.h> // TEST_CASE, ...
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <cstddef> // std::size_t
#include <cstdint> // std::uint16_t
#include <string> // std::string
#include <map> // std::multimap
#include <memory> // std::shared_ptr

TEST_CASE("POST_resource_test")
{
    using namespace std::literals::string_literals;

    static constexpr std::uint16_t port{ 1984U };
    static constexpr char messageToSend[] = "\"Guten Tag\"";

    const std::shared_ptr<cr::rest::Response> response{
        cr::sendRequestSync("localhost", port, cr::HttpVerb::POST,
                            "/resource", messageToSend)
    };

    REQUIRE(response != nullptr);

    REQUIRE(response->get_status_code() == cr::HttpStatusCode::OK);

    const std::multimap<std::string, std::string> headers{
        response->get_headers()
    };

    const auto endIt = std::end(headers);

    static const std::string contentType{ "Content-Type" };
    static const std::string contentLength{ "Content-Length" };

    REQUIRE(headers.find(contentType) != endIt);
    REQUIRE(headers.find(contentType)->second == "application/json"s);

    REQUIRE(headers.find(contentLength) != endIt);

    REQUIRE_NOTHROW(boost::lexical_cast<std::size_t>(headers.find(contentLength)->second));

    const std::size_t length{
        boost::lexical_cast<std::size_t>(headers.find(contentLength)->second)
    };

    // Fetch the response body.
    cr::rest::Http::fetch(length, response);

    const cr::rest::Bytes rawBody{ response->get_body() };
    REQUIRE(rawBody.size() == length);

    // interpret the bytes as string
    const std::string bodyAsString(std::begin(rawBody), std::end(rawBody));

    // parse the string as JSON.
    REQUIRE_NOTHROW(cr::parseJson(bodyAsString));
    const cr::json::Document jsonDoc{
        cr::parseJson(bodyAsString)
    };

    // Create the ExampleType object out of the JSON.
    REQUIRE_NOTHROW(cr::fromJson<cr::ExampleType>(jsonDoc));
    const cr::ExampleType obj{ cr::fromJson<cr::ExampleType>(jsonDoc) };

    CHECK(obj.getStr() == ("You sent "s + messageToSend));
    CHECK(obj.getStruct().i == 5);
    CHECK(obj.getStruct().d == doctest::Approx(5.5));

    REQUIRE(obj.getVec().size() == 2U);
    CHECK(obj.getVec()[0U] == doctest::Approx(1.1));
    CHECK(obj.getVec()[1U] == doctest::Approx(2.2));
}
