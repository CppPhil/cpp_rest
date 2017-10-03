/*!
 * \file response.hpp
 * \brief Exports utilities for responding to requests.
**/
#ifndef INCG_CR_RESPONSE_HPP
#define INCG_CR_RESPONSE_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/http_status_code.hpp" // cr::HttpStatusCode
#include <rapidjson/document.h> // rapidjson::Document
#include <corvusoft/restbed/session.hpp> // restbed::Session
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstddef> // std::size_t

namespace cr
{
/*!
 * \brief Routine to respond to a request by closing a restbed::Session.
 * \param session The session to close.
 * \param httpStatusCode The HTTP status code to use in the reply.
 * \param replyData Pointer to the first (0th) byte of the data to be sent.
 * \param replyDataByteSize The size of the data pointed to by 'replyData'
 *                          in bytes.
 * \param contentType The content type to use, e.g. "application/json".
 * \note Responds with just raw bytes.
**/
void respond(rest::Session &session,
             HttpStatusCode httpStatusCode,
             const void *replyData,
             std::size_t replyDataByteSize,
             boost::string_ref contentType);

/*!
 * \brief Routine to respond to a request by closing a restbed::Session.
 * \param session The session to close.
 * \param httpStatusCode The HTTP status code to use in the reply.
 * \param jsonDocument The JSON document to send.
 * \note Responds with a JSON document.
 *       The Content-Type will be application/json
**/
void respond(rest::Session &session,
             HttpStatusCode httpStatusCode,
             const json::Document &jsonDocument);

/*!
 * \brief Routine to respond to a request by closing a restbed::Session.
 * \param session The session to close.
 * \param httpStatusCode The HTTP status code to use in the reply.
 * \param stringToSend The String to be sent.
 * \note Responds with plain text.
 *       The Content-Type will be text/plain
**/
void respond(rest::Session &session,
             HttpStatusCode httpStatusCode,
             boost::string_ref stringToSend);
} // namespace cr
#endif // INCG_CR_RESPONSE_HPP
