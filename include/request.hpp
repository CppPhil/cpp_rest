/*!
 * \file request.hpp
 * \brief Exports utilities for working with restbed::Requests.
**/
#ifndef INCG_RC_REQUEST_HPP
#define INCG_RC_REQUEST_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/http_verb.hpp" // cr::HttpVerb
#include <rapidjson/document.h> // rapidjson::Document
#include <corvusoft/restbed/request.hpp> // restbed::Request
#include <corvusoft/restbed/response.hpp> // restbed::Response
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstddef> // std::size_t
#include <cstdint> // std::uint16_t
#include <memory> // std::shared_ptr
#include <functional> // std::function
#include <future> // std::future
#include <map> // std::multimap
#include <string> // std::string

namespace cr
{
/*!
 * \brief Returns the Content-Length of a restbed::Request.
 * \param request The request to get the Content-Length of.
 * \return The Content-Length of 'request' or 0 if the header of 'request'
 *         had no Content-Length in it.
**/
std::size_t getContentLength(const rest::Request &request);

/*!
 * \brief Sends a request synchronously.
 * \param requestOutParam Output parameter. The Request created is written
 *                        to the object referenced by this reference.
 *                        The Request must be kept alive as long as the
 *                        Response.
 * \param hostIp The IP address to send the request to.
 * \param port The port on the remote host to send the request to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The resource to send a request to.
 * \param contentType The Content-Type of the request.
 * \param dataToSend Pointer to the first (0th) byte of the memory to send.
 * \param dataToSendByteSize The size of the data pointed to by 'dataToSend'
 *                           in bytes.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return The response received.
 * \note Blocks the calling thread until the response is received.
**/
const std::shared_ptr<rest::Response> sendRequestSync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref contentType,
    const void *dataToSend,
    std::size_t dataToSendByteSize,
    const std::multimap<std::string, std::string> &headers = { },
    const std::multimap<std::string, std::string> &queryParameters = { });

/*!
 * \brief Sends a request asynchronously.
 * \param requestOutParam Output parameter. The Request created is written
 *                        to the object referenced by this reference.
 *                        The Request must be kept alive as long as the
 *                        Response.
 * \param hostIp The IP address to send the request to.
 * \param port The port on the remote host to send the request to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource to send the request to.
 * \param contentType The Content-Type of the request to send.
 * \param dataToSend Pointer to the first (0th) byte of the memory to send.
 * \param dataToSendByteSize The size of the data pointed to by 'dataToSend'
 *                           in bytes.
 * \param callback The callback routine to be called when the response
 *                 is received.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return A future to the response.
 * \note Returns immediately.
**/
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
    const std::multimap<std::string, std::string> &headers = { },
    const std::multimap<std::string, std::string> &queryParameters = { });

/*!
 * \brief Sends a request of JSON data synchronously.
 * \param requestOutParam Output parameter. The Request created is written
 *                        to the object referenced by this reference.
 *                        The Request must be kept alive as long as the
 *                        Response.
 * \param hostIp The IP address to send the JSON data to.
 * \param port The port on the remote host to send the JSON data to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource to send the JSON data to.
 * \param json The JSON data to send.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return The response.
 * \note Blocks the calling thread until the response is received.
**/
const std::shared_ptr<rest::Response> sendRequestSync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    const json::Document &json,
    const std::multimap<std::string, std::string> &headers = { },
    const std::multimap<std::string, std::string> &queryParameters = { });

/*!
 * \brief Sends a request of JSON data asynchronously.
 * \param requestOutParam Output parameter. The Request created is written
 *                        to the object referenced by this reference.
 *                        The Request must be kept alive as long as the
 *                        Response.
 * \param hostIp The IP address to send the JSON data to.
 * \param port The port on the remote host to send the JSON data to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource to send the JSON data to.
 * \param json The JSON data to send.
 * \param callback The callback routine to be called when the response is
 *                 received.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return A future to the response.
 * \note Returns immediately.
**/
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
    const std::multimap<std::string, std::string> &headers = { },
    const std::multimap<std::string, std::string> &queryParameters = { });

/*!
 * \brief Sends a plain text string synchronously.
 * \param requestOutParam Output parameter. The Request created is written
 *                        to the object referenced by this reference.
 *                        The Request must be kept alive as long as the
 *                        Response.
 * \param hostIp The IP address to send the string to.
 * \param port The port on the remote host to send the string to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource to send the request to.
 * \param stringToSend The string to be sent as the body of the request.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return The response received.
 * \note Blocks the calling thread until the response is received.
**/
const std::shared_ptr<rest::Response> sendRequestSync(
    std::shared_ptr<rest::Request> &requestOutParam,
    boost::string_ref hostIp,
    std::uint16_t port,
    HttpVerb httpVerb,
    boost::string_ref pathToResource,
    boost::string_ref stringToSend,
    const std::multimap<std::string, std::string> &headers = { },
    const std::multimap<std::string, std::string> &queryParameters = { });

/*!
 * \brief Asynchronously sends a request containing a string.
 * \param requestOutParam Output parameter. The Request created is written
 *                        to the object referenced by this reference.
 *                        The Request must be kept alive as long as the
 *                        Response.
 * \param hostIp The IP address to send the request to.
 * \param port The port on the remote host to send the request to.
 * \param httpVerb The HTTP verb to use.
 * \param pathToResource The REST resource to send the request to.
 * \param stringToSend The plain text string to be used as the body of the
 *                     request.
 * \param callback The callback routine to be called as soon as the response
 *                 is received.
 * \param headers The headers to use, can be used to pass header parameters.
 * \param queryParameters The query parameters. Used to pass query parameters.
 * \return A future of the response.
 * \note Returns immediately.
**/
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
    const std::multimap<std::string, std::string> &headers = { },
    const std::multimap<std::string, std::string> &queryParameters = { });
} // namespace cr
#endif // INCG_RC_REQUEST_HPP
