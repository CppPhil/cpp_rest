#include "../include/example_rest_api.hpp"
#include "../include/example_type.hpp" // cr::ExampleType
#include "../include/json.hpp" // cr::asJson
#include <boost/lexical_cast.hpp> // boost::lexical_cast

namespace cr
{
ExampleRestApi::ExampleRestApi()
    : base_type{ this }
{
    registerResource("/resource",
                     HttpVerb::POST,
                     &ExampleRestApi::handlePostResource);
}

ExampleRestApi::~ExampleRestApi() = default;

ExampleRestApi &ExampleRestApi::start(std::uint16_t port)
{
    startRestApi(port);
    return *this;
}

void ExampleRestApi::handlePostResource(rest::Session &session)
{

    const auto request = session.get_request();
    std::size_t content_length = request->get_header("Content-Length", 0U);

    session.fetch(content_length, [](const std::shared_ptr<rest::Session> session,
                                     const rest::Bytes &body) {

        using namespace std::literals::string_literals;
        const std::string string(std::begin(body), std::end(body));
        const cr::ExampleType obj{ "You sent "s + string,
                                   { 5, 5.5 },
                                   { 1.1, 2.2 } };
        const std::string s{ jsonAsText(asJson(obj)) };

        const rest::Bytes bytes(std::begin(s), std::end(s));

        const std::multimap<std::string, std::string> headers{
            { "Content-Length", boost::lexical_cast<std::string>(bytes.size()) },
            { "Content-Type", "application/json" }
        };

        session->close(rest::OK, bytes, headers);
    });
}
} // namespace cr
