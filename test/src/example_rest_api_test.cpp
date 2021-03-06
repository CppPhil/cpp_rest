#include "../../include/namespace_aliases.hpp"
#include "../../include/http_verb.hpp" // cr::HttpVerb
#include "../../include/request.hpp" // cr::sendRequestSync
#include "../../include/http_status_code.hpp" // cr::HttpStatusCode
#include "../../include/json.hpp" // cr::parseJson, cr::fromJson
#include "../../include/example_type.hpp" // cr::ExampleType
#include "../../include/example_rest_api.hpp" // cr::ExampleRestApi
#include "../../include/rest_controller.hpp" // cr::RestController
#include <corvusoft/restbed/settings.hpp> // restbed::Settings
#include <corvusoft/restbed/response.hpp> // restbed::Response
#include <corvusoft/restbed/http.hpp> // restbed::Http::fetch
#include <doctest.h> // TEST_CASE, ...
#include <gsl/gsl> // gsl::finally
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <cstddef> // std::size_t
#include <cstdint> // std::uint16_t
#include <string> // std::string
#include <map> // std::multimap
#include <memory> // std::shared_ptr

namespace
{
constexpr std::uint16_t port{ 1984U };
constexpr char ipv4Localhost[] = "127.0.0.1";
constexpr char contentType[] = "Content-Type";
constexpr char contentLength[] = "Content-Length";
} // anonymous namespace

TEST_CASE("example_rest_api_test")
{
    cr::RestController<cr::ExampleRestApi> restApi{ "example_test.log" };
    std::future<void> restApiFuture{ restApi.start(port) };

    SUBCASE("POST_resource_test") {
        auto finalAction = gsl::finally([&restApi, &restApiFuture] {
            restApi.stop();
            restApiFuture.wait();
        });

        using namespace std::literals::string_literals;

        static constexpr char messageToSend[] = "\"Guten Tag\"";

        std::shared_ptr<cr::rest::Request> request{ nullptr };
        const std::shared_ptr<cr::rest::Response> response{
            cr::sendRequestSync(
                request,
                ipv4Localhost, port, cr::HttpVerb::POST,
                "/resource", messageToSend)
        };

        REQUIRE(response != nullptr);

        CHECK(response->get_status_code() == cr::HttpStatusCode::OK);

        const std::multimap<std::string, std::string> headers{
            response->get_headers()
        };

        const auto endIt = std::end(headers);

        REQUIRE(headers.find(contentType) != endIt);
        REQUIRE(headers.find(contentType)->second == "application/json"s);

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

    SUBCASE("POST_resource2_positive_test") {
        auto finalAction = gsl::finally([&restApi, &restApiFuture] {
            restApi.stop();
            restApiFuture.wait();
        });

        using namespace std::literals::string_literals;

        const cr::ExampleType testObject{ "TEST_TEXT"s,
                                          { 1, 2.734 },
                                          {3.3, 4.4, 1.1, 5.23456 } };

        const cr::json::Document jsonDocument{
            cr::asJson(testObject)
        };

        std::shared_ptr<cr::rest::Request> request{ nullptr };
        const std::shared_ptr<cr::rest::Response> response{
            cr::sendRequestSync(
                request,
                ipv4Localhost, port,
                cr::HttpVerb::POST, "/resource2",
                jsonDocument)
        };

        REQUIRE(response != nullptr);

        CHECK(response->get_status_code() == cr::HttpStatusCode::ACCEPTED);

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

        CHECK(bodyAsString == "Thanks for the data."s);
    }

    SUBCASE("POST_resource2_no_json_sent") {
        auto finalAction = gsl::finally([&restApi, &restApiFuture] {
            restApi.stop();
            restApiFuture.wait();
        });

        std::shared_ptr<cr::rest::Request> request{ nullptr };
        const std::shared_ptr<cr::rest::Response> response{
            cr::sendRequestSync(
                request,
                ipv4Localhost, port, cr::HttpVerb::POST,
                "/resource2", "This isn't JSON.")
        };

        REQUIRE(response != nullptr);

        CHECK(response->get_status_code() == cr::HttpStatusCode::BAD_REQUEST);
    }

    SUBCASE("POST_resource2_invalid_json") {
        auto finalAction = gsl::finally([&restApi, &restApiFuture] {
            restApi.stop();
            restApiFuture.wait();
        });

        static constexpr char json[] = R"(
                                          {
                                              "str": "Text",
                                              "moreText": "testtesttest",
                                              "obj": {
                                                  "val": 5.5,
                                                  "int": 1
                                              }
                                          }
                                       )";

        REQUIRE_NOTHROW(cr::parseJson(json));

        const cr::json::Document jsonDocument{
            cr::parseJson(json)
        };

        std::shared_ptr<cr::rest::Request> request{ nullptr };
        const std::shared_ptr<cr::rest::Response> response{
            cr::sendRequestSync(
                request,
                ipv4Localhost, port, cr::HttpVerb::POST,
                "/resource2", jsonDocument)
        };

        REQUIRE(response != nullptr);

        CHECK(response->get_status_code() == cr::HttpStatusCode::IM_A_TEAPOT);
    }
}
