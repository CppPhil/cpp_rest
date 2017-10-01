#include <functional>
#include <memory>
#include <cstdlib>
#include <restbed>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <boost/lexical_cast.hpp>
#include <gsl/gsl_util>
#include "../include/example_rest_api.hpp"

using namespace std;
using namespace restbed;

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );

        rapidjson::StringBuffer sb{ };
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
    } );
}

int main() {
    /*
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "POST", post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port(1984);
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );
    */

    cr::ExampleRestApi exampleRestApi{ };
    static constexpr std::uint16_t port = 1984U;
    exampleRestApi.start(port);
}
