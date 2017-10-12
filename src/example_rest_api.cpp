#include "../include/example_rest_api.hpp"
#include "../include/example_type.hpp" // cr::ExampleType
#include "../include/json.hpp" // cr::asJson
#include "../include/request.hpp" // cr::getContentLength
#include "../include/response.hpp" // cr::respond
#include "../include/log.hpp" // CR_LOG
#include <boost/current_function.hpp> // BOOST_CURRENT_FUNCTION
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <string> // std::string, std::literals::string_literals::operator""s
#include <utility> // std::move

namespace cr
{
ExampleRestApi::ExampleRestApi(std::string restbedLogFilePath)
    : base_type{ this, std::move(restbedLogFilePath), "127.0.0.1" }
{
    // Register the REST resources ...

    registerResource(
        "/resource",
        HttpVerb::POST,
        &ExampleRestApi::handlePostResource);

    registerResource(
        "/resource2",
        HttpVerb::POST,
        &ExampleRestApi::handlePostResource2);
}

ExampleRestApi::~ExampleRestApi() = default;

ExampleRestApi &ExampleRestApi::start(std::uint16_t port)
{
    startRestApi(port);
    return *this;
}

void ExampleRestApi::handlePostResource(rest::Session &session)
{
    const std::shared_ptr<const rest::Request> request{
        session.get_request()
    };

    if (request == nullptr) {
        CR_LOG(LogLevel::error) << "request was nullptr";
        return;
    }

    const std::size_t contentLength{ getContentLength(*request) };

    // Fetch contentLength bytes and then reply to the request.
    session.fetch(contentLength,
                  [](const std::shared_ptr<rest::Session> session,
                     const rest::Bytes &body) {

        using namespace std::literals::string_literals;
        // Interpret the bytes of the body of the request as a string.
        const std::string string(std::begin(body), std::end(body));

        // Create the object to respond with.
        const cr::ExampleType obj{ "You sent "s + string,
                                   { 5, 5.5 },
                                   { 1.1, 2.2 } };

        // Turn 'obj' into a JSON document.
        const json::Document responseJson{ asJson(obj) };

        // Respond by closing the session, replying with the JSON document
        // and the HTTP status code set to 'OK'.
        respond(*session, HttpStatusCode::OK, responseJson);
    });
}

void ExampleRestApi::handlePostResource2(rest::Session &session)
{
    using namespace std::literals::string_literals;

    const std::shared_ptr<const rest::Request> request{
        session.get_request()
    };

    if (request == nullptr) {
        CR_LOG(LogLevel::error) << "request was nullptr";
        return;
    }

    const std::size_t contentLength{ getContentLength(*request) };

    // Fetch contentLength bytes and then reply to the request.
    session.fetch(contentLength,
                  [](const std::shared_ptr<rest::Session> session,
                     const rest::Bytes &body) {
        // Interpret the bytes of the body of the request as a String.
        const std::string s(std::begin(body), std::end(body));

        try {
            // Try to parse the request body as JSON
            // and then try to create an ExampleType object from the JSON.
            const ExampleType o{ fromJson<ExampleType>(parseJson(s)) };

            // Print the object to the log.
            CR_LOG(LogLevel::info)
                      << "Just got ExampleType object in "
                      << BOOST_CURRENT_FUNCTION
                      << ":\n" << o;
        } catch (const FailedToParseJsonException &ex) {
            CR_LOG(LogLevel::error) << "Got invalid data: \n" << s;

            // The data could not be parsed as JSON.
            const std::string replStr{ "Data received was not JSON.\n"s
                                       + ex.what() };

            // Respond with error message.
            respond(*session, HttpStatusCode::BAD_REQUEST, replStr);
            return; // Exit the lambda.
        } catch (const InvalidJsonException &ex) {
            CR_LOG(LogLevel::error) << "Invalid JSON: \n" << s;

            // The data was JSON, but the contents were not correct.
            const std::string replStr{ "The JSON received was not valid.\n"s
                                       + ex.what() };

            // Respond with error message.
            respond(*session, HttpStatusCode::IM_A_TEAPOT, replStr);
            return; // Exit the lambda.
        }

        // Everything was OK. Respond with reply indicating success.
        respond(*session, HttpStatusCode::ACCEPTED, "Thanks for the data.");
    });
}
} // namespace cr
