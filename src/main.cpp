#include <memory>
#include <cstdlib>
#include <restbed>
#include <json.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace restbed;

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );

    int content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );

        nlohmann::json jsonObject{ };
        jsonObject["test"] = "String";
        const auto s = jsonObject.dump();
        const restbed::Bytes bytes(std::begin(s), std::end(s));

        const std::multimap<std::string, std::string> headers{
            { "Content-Length", boost::lexical_cast<std::string>(bytes.size()) },
            { "Content-Type", "application/json" }
        };

        session->close(OK, bytes, headers);
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "POST", post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port(1984);
    settings->set_default_header( "Connection", "close" );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
