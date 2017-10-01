#include "../include/example_rest_api.hpp"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <boost/lexical_cast.hpp>

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
    /*
     * rapidjson::StringBuffer sb{ };
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
        {
            writer.StartObject();
            const auto finalAct = gsl::finally([&writer] { writer.EndObject(); });
            writer.String("test");
            writer.String("String");
        }
        const std::string s{ sb.GetString() };
        const restbed::Bytes bytes(std::begin(s), std::end(s));

        const std::multimap<std::string, std::string> headers{
            { "Content-Length", boost::lexical_cast<std::string>(bytes.size()) },
            { "Content-Type", "application/json" }
        };

        session->close(OK, bytes, headers);
     * */

    const auto request = session.get_request();
    int content_length = request->get_header("Content-Length", 0);

    session.fetch(content_length, [](const std::shared_ptr<rest::Session> session,
                                     const rest::Bytes &body) {

        json::StringBuffer sb{ };
        json::PrettyWriter<json::StringBuffer> writer{ sb };
        writer.StartObject();
        writer.String("You sent: ");
        std::string s(body.size(), '\0');
        std::copy(std::begin(body), std::end(body), std::begin(s));
        writer.String(s.data());
        writer.EndObject();
        s = sb.GetString();

        const rest::Bytes bytes(std::begin(s), std::end(s));

        const std::multimap<std::string, std::string> headers{
            { "Content-Length", boost::lexical_cast<std::string>(bytes.size()) },
            { "Content-Type", "application/json" }
        };

        session->close(rest::OK, bytes, headers);
    });
}
} // namespace cr
