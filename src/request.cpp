#include "../include/request.hpp"
#include "../include/json.hpp" // cr::jsonAsText
#include <corvusoft/restbed/settings.hpp> // restbed::Settings
#include <corvusoft/restbed/http.hpp> // restbed::Http::sync, restbed::Http:async
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <string> // std::string, std::literals::string_literals::operator""s

namespace cr
{
std::size_t getContentLength(const rest::Request &request)
{
    using namespace std::literals::string_literals;

    // return this value if there is no "Content-Length" in the header.
    static constexpr std::size_t fallbackValue{ 0U };

    return request.get_header("Content-Length"s, fallbackValue);
}

namespace
{
/*!
 * \brief Creates a restbed::request out of raw memory.
 * \param hostIp The IP to use for the host to send the request to.
 * \param port The port on the remote host.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource that the request will be sent to.
 * \param contentType The Content-Type of the body.
 * \param dataToSend Pointer to the first (0th) byte of the memory to be
 *                   used as the body of the request.
 * \param dataToSendByteSize The size of the data pointed to by 'dataToSend'
 *                           in bytes.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return The request object created.
**/
std::shared_ptr<rest::Request> makeRequest(
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref contentType,
    const void *dataToSend,
    std::size_t dataToSendByteSize,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    static constexpr char contentTypeStr[] = "Content-Type";
    static constexpr char contentLenStr[]  = "Content-Length";

    std::shared_ptr<rest::Request> request{ std::make_shared<rest::Request>() };

    request->set_host(hostIp.data());
    request->set_port(port);
    request->set_method(boost::lexical_cast<std::string>(httpVerb));
    request->set_path(pathToResource.data());

    const unsigned char * const begin{
        static_cast<const unsigned char *>(dataToSend)
    };
    const unsigned char * const end{
        begin + dataToSendByteSize
    };
    const rest::Bytes body(begin, end);

    request->set_body(body);

    request->set_headers(headers);
    request->add_header(contentTypeStr, contentType.data());
    request->add_header(
        contentLenStr,
        boost::lexical_cast<std::string>(body.size()));
    request->set_query_parameters(queryParameters);

    return request;
}

/*!
 * \brief Creates a request object for JSON data.
 * \param hostIp The IP that the request will be sent to.
 * \param port The port that the request will be sent to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource that the request will be sent to.
 * \param json The JSON data to use as the body.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return The request object created.
**/
std::shared_ptr<rest::Request> makeRequest(
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    const json::Document &json,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    static constexpr char jsonContentType[] = "application/json";

    const std::string jsonStr{ jsonAsText(json) };

    return makeRequest(
               hostIp, port, httpVerb, pathToResource, jsonContentType,
               jsonStr.data(), jsonStr.size(), headers, queryParameters);
}

/*!
 * \brief Creates a request with a plain text body.
 * \param hostIp The IP address that the request will be sent to.
 * \param port The port that the request will be sent to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource to send the request to.
 * \param stringToSend The plain text string to use as the body of
 *                     the request.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return The request object created.
**/
std::shared_ptr<rest::Request> makeRequest(
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref stringToSend,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    static constexpr char stringContentType[] = "text/plain";

    return makeRequest(
               hostIp, port, httpVerb, pathToResource,
               stringContentType, stringToSend.data(),
               stringToSend.size(), headers, queryParameters);
}
} // anonymous namespace

const std::shared_ptr<rest::Response> sendRequestSync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref contentType,
    const void *dataToSend,
    std::size_t dataToSendByteSize,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    requestOutParam = makeRequest(
        hostIp, port, httpVerb, pathToResource,
        contentType, dataToSend,
        dataToSendByteSize, headers,
        queryParameters);

    return rest::Http::sync(requestOutParam);
}

std::future<std::shared_ptr<rest::Response>> sendRequestAsync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref contentType,
    const void *dataToSend,
    std::size_t dataToSendByteSize,
    const std::function<void (
        const std::shared_ptr<rest::Request>,
        const std::shared_ptr<rest::Response>)> &callback,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    requestOutParam = makeRequest(
        hostIp, port, httpVerb, pathToResource,
        contentType, dataToSend,
        dataToSendByteSize, headers,
        queryParameters);

    return rest::Http::async(
        requestOutParam,
        callback);
}

const std::shared_ptr<rest::Response> sendRequestSync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    const json::Document &json,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    requestOutParam = makeRequest(
        hostIp, port, httpVerb, pathToResource,
        json, headers, queryParameters);

    return rest::Http::sync(requestOutParam);
}

std::future<std::shared_ptr<rest::Response>> sendRequestAsync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    const json::Document &json,
    const std::function<void (
        const std::shared_ptr<rest::Request>,
        const std::shared_ptr<rest::Response>)> &callback,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    requestOutParam = makeRequest(
        hostIp, port, httpVerb, pathToResource,
        json, headers, queryParameters);

    return rest::Http::async(
        requestOutParam,
        callback);
}

const std::shared_ptr<rest::Response> sendRequestSync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref stringToSend,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    requestOutParam = makeRequest(
        hostIp, port, httpVerb, pathToResource,
        stringToSend, headers, queryParameters);

    return rest::Http::sync(requestOutParam);
}

std::future<std::shared_ptr<rest::Response>> sentRequestAsync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref stringToSend,
    const std::function<void (
        const std::shared_ptr<rest::Request>,
        const std::shared_ptr<rest::Response>)> &callback,
    const std::multimap<std::string, std::string> &headers,
    const std::multimap<std::string, std::string> &queryParameters)
{
    requestOutParam = makeRequest(
        hostIp, port, httpVerb, pathToResource,
        stringToSend, headers, queryParameters);

    return rest::Http::async(
        requestOutParam,
        callback);
}
} // namespace cr
