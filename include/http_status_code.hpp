#ifndef INCG_CR_HTTP_STATUS_CODE_HPP
#define INCG_CR_HTTP_STATUS_CODE_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/except.hpp" // cr::InvalidEnumeratorValueException, CR_THROW_WITH_SOURCE_INFO
#include <corvusoft/restbed/status_code.hpp> // restbed::CONTINUE, restbed::SWITCHING_PROTOCOLS, ...
#include <iosfwd> // std::ostream

namespace cr
{
/*!
 * \brief Scoped enum for the HTTP status codes.
**/
enum class HttpStatusCode : int
{
    // 1xx Informational responses
    CONTINUE                        = rest::CONTINUE,
    SWITCHING_PROTOCOLS             = rest::SWITCHING_PROTOCOLS,
    PROCESSING                      = rest::PROCESSING,

    // 2xx Success
    OK                              = rest::OK,
    CREATED                         = rest::CREATED,
    ACCEPTED                        = rest::ACCEPTED,
    NON_AUTHORITATIVE_INFORMATION   = rest::NON_AUTHORITATIVE_INFORMATION,
    NO_CONTENT                      = rest::NO_CONTENT,
    RESET_CONTENT                   = rest::RESET_CONTENT,
    PARTIAL_CONTENT                 = rest::PARTIAL_CONTENT,
    MULTI_STATUS                    = rest::MULTI_STATUS,
    ALREADY_REPORTED                = rest::ALREADY_REPORTED,
    IM_USED                         = rest::IM_USED,

    // 3xx Redirection
    MULTIPLE_CHOICES                = rest::MULTIPLE_CHOICES,
    MOVED_PERMANENTLY               = rest::MOVED_PERMANENTLY,
    FOUND                           = rest::FOUND,
    SEE_OTHER                       = rest::SEE_OTHER,
    NOT_MODIFIED                    = rest::NOT_MODIFIED,
    USE_PROXY                       = rest::USE_PROXY,
    SWITCH_PROXY                    = 306,
    TEMPORARY_REDIRECT              = rest::TEMPORARY_REDIRECT,
    PERMANENT_REDIRECT              = rest::PERMANENT_REDIRECT,

    // 4xx Client errors
    BAD_REQUEST                     = rest::BAD_REQUEST,
    UNAUTHORIZED                    = rest::UNAUTHORIZED,
    PAYMENT_REQUIRED                = rest::PAYMENT_REQUIRED,
    FORBIDDEN                       = rest::FORBIDDEN,
    NOT_FOUND                       = rest::NOT_FOUND,
    METHOD_NOT_ALLOWED              = rest::METHOD_NOT_ALLOWED,
    NOT_ACCEPTABLE                  = rest::NOT_ACCEPTABLE,
    PROXY_AUTHENTICATION_REQUIRED   = rest::PROXY_AUTHENTICATION_REQUIRED,
    REQUEST_TIMEOUT                 = rest::REQUEST_TIMEOUT,
    CONFLICT                        = rest::CONFLICT,
    GONE                            = rest::GONE,
    LENGTH_REQUIRED                 = rest::LENGTH_REQUIRED,
    PRECONDITION_FAILED             = rest::PRECONDITION_FAILED,
    REQUEST_ENTITY_TOO_LARGE        = rest::REQUEST_ENTITY_TOO_LARGE,
    REQUEST_URI_TOO_LONG            = rest::REQUEST_URI_TOO_LONG,
    UNSUPPORTED_MEDIA_TYPE          = rest::UNSUPPORTED_MEDIA_TYPE,
    REQUESTED_RANGE_NOT_SATISFIABLE = rest::REQUESTED_RANGE_NOT_SATISFIABLE,
    EXPECTATION_FAILED              = rest::EXPECTATION_FAILED,
    IM_A_TEAPOT                     = 418,
    MISDIRECTED_REQUEST             = 421,
    UNPROCESSABLE_ENTITY            = rest::UNPROCESSABLE_ENTITY,
    LOCKED                          = rest::LOCKED,
    FAILED_DEPENDENCY               = rest::FAILED_DEPENDENCY,
    UPGRADE_REQUIRED                = rest::UPGRADE_REQUIRED,
    PRECONDITION_REQUIRED           = rest::PRECONDITION_REQUIRED,
    TOO_MANY_REQUESTS               = rest::TOO_MANY_REQUESTS,
    REQUEST_HEADER_FIELDS_TOO_LARGE = rest::REQUEST_HEADER_FIELDS_TOO_LARGE,
    UNAVAILABLE_FOR_LEGAL_REASONS   = 451,

    // 5xx Server errors
    INTERNAL_SERVER_ERROR           = rest::INTERNAL_SERVER_ERROR,
    NOT_IMPLEMENTED                 = rest::NOT_IMPLEMENTED,
    BAD_GATEWAY                     = rest::BAD_GATEWAY,
    SERVICE_UNAVAILABLE             = rest::SERVICE_UNAVAILABLE,
    GATEWAY_TIMEOUT                 = rest::GATEWAY_TIMEOUT,
    HTTP_VERSION_NOT_SUPPORTED      = rest::HTTP_VERSION_NOT_SUPPORTED,
    VARIANT_ALSO_NEGOTIATES         = rest::VARIANT_ALSO_NEGOTIATES,
    INSUFFICIENT_STORAGE            = rest::INSUFFICIENT_STORAGE,
    LOOP_DETECTED                   = rest::LOOP_DETECTED,
    NOT_EXTENDED                    = rest::NOT_EXTENDED,
    NETWORK_AUTHENTICATION_REQUIRED = rest::NETWORK_AUTHENTICATION_REQUIRED
};

/*!
 * \brief Prints a HttpStatusCode to 'os'.
 * \param os The ostream to print to.
 * \param httpStatusCode The HttpStatusCode to print.
 * \return A reference to 'os'.
 * \throws cr::InvalidEnumeratorValueException if 'httpStatusCode' had an
 *         invalid value.
**/
std::ostream &operator<<(std::ostream &os, HttpStatusCode httpStatusCode);

/*!
 * \brief Compares the underlying int value of 'statusCode' to 'num'.
 * \param statusCode The first operand.
 * \param num The second operand.
 * \return true if the two operands are considered equal, otherwise false.
**/
bool operator==(HttpStatusCode statusCode, int num);

/*!
 * \brief Compares the underlying int value of 'statusCode' to 'num'.
 * \param num The first operand.
 * \param statusCode The second operand.
 * \return true if the two operands are considered equal, otherwise false.
**/
bool operator==(int num, HttpStatusCode statusCode);

/*!
 * \brief Compares the underlying int value of 'statusCode' to 'num'.
 * \param statusCode The first operand.
 * \param num The second operand.
 * \return true if the two operands are considered not equal, otherwise false.
**/
bool operator!=(HttpStatusCode statusCode, int num);

/*!
 * \brief Compares the underlying int value of 'statusCode' to 'num'.
 * \param num The first operand.
 * \param statusCode The second operand.
 * \return true if the two operands are considered not equal, otherwise false.
**/
bool operator!=(int num, HttpStatusCode statusCode);
} // namespace cr
#endif // INCG_CR_HTTP_STATUS_CODE_HPP
