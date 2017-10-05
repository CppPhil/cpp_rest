#include "../include/http_status_code.hpp"
#include "../include/stringify.hpp" // CR_STRINGIFY
#include <ciso646> // not
#include <ostream> // std::ostream
#include <type_traits> // std::underlying_type_t

/*!
 * \def CR_DETAIL_PRINT_STATUS_CODE(statusCode)
 * \brief Implementation macro of
 *        std::ostream &operator<<(std::ostream &os, HttpStatusCode httpStatusCode).
**/
#define CR_DETAIL_PRINT_STATUS_CODE(statusCode) \
    case ::cr::HttpStatusCode::statusCode: \
        os << CR_STRINGIFY(statusCode); \
        break

namespace cr
{
std::ostream &operator<<(std::ostream &os, HttpStatusCode httpStatusCode)
{
    switch (httpStatusCode) {
    CR_DETAIL_PRINT_STATUS_CODE(CONTINUE);
    CR_DETAIL_PRINT_STATUS_CODE(SWITCHING_PROTOCOLS);
    CR_DETAIL_PRINT_STATUS_CODE(PROCESSING);
    CR_DETAIL_PRINT_STATUS_CODE(OK);
    CR_DETAIL_PRINT_STATUS_CODE(CREATED);
    CR_DETAIL_PRINT_STATUS_CODE(ACCEPTED);
    CR_DETAIL_PRINT_STATUS_CODE(NON_AUTHORITATIVE_INFORMATION);
    CR_DETAIL_PRINT_STATUS_CODE(NO_CONTENT);
    CR_DETAIL_PRINT_STATUS_CODE(RESET_CONTENT);
    CR_DETAIL_PRINT_STATUS_CODE(PARTIAL_CONTENT);
    CR_DETAIL_PRINT_STATUS_CODE(MULTI_STATUS);
    CR_DETAIL_PRINT_STATUS_CODE(ALREADY_REPORTED);
    CR_DETAIL_PRINT_STATUS_CODE(IM_USED);
    CR_DETAIL_PRINT_STATUS_CODE(MULTIPLE_CHOICES);
    CR_DETAIL_PRINT_STATUS_CODE(MOVED_PERMANENTLY);
    CR_DETAIL_PRINT_STATUS_CODE(FOUND);
    CR_DETAIL_PRINT_STATUS_CODE(SEE_OTHER);
    CR_DETAIL_PRINT_STATUS_CODE(NOT_MODIFIED);
    CR_DETAIL_PRINT_STATUS_CODE(USE_PROXY);
    CR_DETAIL_PRINT_STATUS_CODE(SWITCH_PROXY);
    CR_DETAIL_PRINT_STATUS_CODE(TEMPORARY_REDIRECT);
    CR_DETAIL_PRINT_STATUS_CODE(PERMANENT_REDIRECT);
    CR_DETAIL_PRINT_STATUS_CODE(BAD_REQUEST);
    CR_DETAIL_PRINT_STATUS_CODE(UNAUTHORIZED);
    CR_DETAIL_PRINT_STATUS_CODE(PAYMENT_REQUIRED);
    CR_DETAIL_PRINT_STATUS_CODE(FORBIDDEN);
    CR_DETAIL_PRINT_STATUS_CODE(NOT_FOUND);
    CR_DETAIL_PRINT_STATUS_CODE(METHOD_NOT_ALLOWED);
    CR_DETAIL_PRINT_STATUS_CODE(NOT_ACCEPTABLE);
    CR_DETAIL_PRINT_STATUS_CODE(PROXY_AUTHENTICATION_REQUIRED);
    CR_DETAIL_PRINT_STATUS_CODE(REQUEST_TIMEOUT);
    CR_DETAIL_PRINT_STATUS_CODE(CONFLICT);
    CR_DETAIL_PRINT_STATUS_CODE(GONE);
    CR_DETAIL_PRINT_STATUS_CODE(LENGTH_REQUIRED);
    CR_DETAIL_PRINT_STATUS_CODE(PRECONDITION_FAILED);
    CR_DETAIL_PRINT_STATUS_CODE(REQUEST_ENTITY_TOO_LARGE);
    CR_DETAIL_PRINT_STATUS_CODE(REQUEST_URI_TOO_LONG);
    CR_DETAIL_PRINT_STATUS_CODE(UNSUPPORTED_MEDIA_TYPE);
    CR_DETAIL_PRINT_STATUS_CODE(REQUESTED_RANGE_NOT_SATISFIABLE);
    CR_DETAIL_PRINT_STATUS_CODE(EXPECTATION_FAILED);
    CR_DETAIL_PRINT_STATUS_CODE(IM_A_TEAPOT);
    CR_DETAIL_PRINT_STATUS_CODE(MISDIRECTED_REQUEST);
    CR_DETAIL_PRINT_STATUS_CODE(UNPROCESSABLE_ENTITY);
    CR_DETAIL_PRINT_STATUS_CODE(LOCKED);
    CR_DETAIL_PRINT_STATUS_CODE(FAILED_DEPENDENCY);
    CR_DETAIL_PRINT_STATUS_CODE(UPGRADE_REQUIRED);
    CR_DETAIL_PRINT_STATUS_CODE(PRECONDITION_REQUIRED);
    CR_DETAIL_PRINT_STATUS_CODE(TOO_MANY_REQUESTS);
    CR_DETAIL_PRINT_STATUS_CODE(REQUEST_HEADER_FIELDS_TOO_LARGE);
    CR_DETAIL_PRINT_STATUS_CODE(UNAVAILABLE_FOR_LEGAL_REASONS);
    CR_DETAIL_PRINT_STATUS_CODE(INTERNAL_SERVER_ERROR);
    CR_DETAIL_PRINT_STATUS_CODE(NOT_IMPLEMENTED);
    CR_DETAIL_PRINT_STATUS_CODE(BAD_GATEWAY);
    CR_DETAIL_PRINT_STATUS_CODE(SERVICE_UNAVAILABLE);
    CR_DETAIL_PRINT_STATUS_CODE(GATEWAY_TIMEOUT);
    CR_DETAIL_PRINT_STATUS_CODE(HTTP_VERSION_NOT_SUPPORTED);
    CR_DETAIL_PRINT_STATUS_CODE(VARIANT_ALSO_NEGOTIATES);
    CR_DETAIL_PRINT_STATUS_CODE(INSUFFICIENT_STORAGE);
    CR_DETAIL_PRINT_STATUS_CODE(LOOP_DETECTED);
    CR_DETAIL_PRINT_STATUS_CODE(NOT_EXTENDED);
    CR_DETAIL_PRINT_STATUS_CODE(NETWORK_AUTHENTICATION_REQUIRED);
    default:
        CR_THROW_WITH_SOURCE_INFO(InvalidEnumeratorValueException,
                                  "httpStatusCode was invalid.");
    }

    return os;
}
#undef CR_DETAIL_PRINT_STATUS_CODE

bool operator==(HttpStatusCode statusCode, int num)
{
    return static_cast<std::underlying_type_t<HttpStatusCode>>(statusCode)
        == num;
}

bool operator==(int num, HttpStatusCode statusCode)
{
    return statusCode == num;
}

bool operator!=(HttpStatusCode statusCode, int num)
{
    return not (statusCode == num);
}

bool operator!=(int num, HttpStatusCode statusCode)
{
    return statusCode != num;
}
} // namespace cr
