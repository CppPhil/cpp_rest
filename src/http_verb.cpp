#include "../include/http_verb.hpp"
#include "../include/stringify.hpp" // CR_STRINGIFY
#include "../include/except.hpp" // cr::InvalidEnumeratorValueException, CR_THROW_WITH_SOURCE_INFO
#include <ostream> // std::ostream
#include <stdexcept> // std::logic_error
#include <string> // std::string, std::literals::string_literals::operator""s

/*!
 * \def CR_DETAIL_HTTP_VERB_PRINT(httpVerb)
 * \brief Implementation macro to print an HTTP verb.
**/
#define CR_DETAIL_HTTP_VERB_PRINT(httpVerb) \
    case HttpVerb::httpVerb: os << CR_STRINGIFY(httpVerb); \
                             break

namespace cr
{
std::ostream &operator<<(std::ostream &os, HttpVerb httpVerb)
{
    switch (httpVerb) {
    CR_DETAIL_HTTP_VERB_PRINT(GET);
    CR_DETAIL_HTTP_VERB_PRINT(POST);
    CR_DETAIL_HTTP_VERB_PRINT(PUT);
    CR_DETAIL_HTTP_VERB_PRINT(PATCH);
    CR_DETAIL_HTTP_VERB_PRINT(DELETE);
    CR_DETAIL_HTTP_VERB_PRINT(COPY);
    CR_DETAIL_HTTP_VERB_PRINT(HEAD);
    CR_DETAIL_HTTP_VERB_PRINT(OPTIONS);
    CR_DETAIL_HTTP_VERB_PRINT(LINK);
    CR_DETAIL_HTTP_VERB_PRINT(UNLINK);
    CR_DETAIL_HTTP_VERB_PRINT(PURGE);
    CR_DETAIL_HTTP_VERB_PRINT(LOCK);
    CR_DETAIL_HTTP_VERB_PRINT(UNLOCK);
    CR_DETAIL_HTTP_VERB_PRINT(PROPFIND);
    CR_DETAIL_HTTP_VERB_PRINT(VIEW);
    CR_DETAIL_HTTP_VERB_PRINT(CONNECT);
    CR_DETAIL_HTTP_VERB_PRINT(TRACE);
    default:
        CR_THROW_WITH_SOURCE_INFO(InvalidEnumeratorValueException,
                                  "enumerator had invalid value");
    }

    return os;
}
} // namespace cr

#undef CR_DETAIL_HTTP_VERB_PRINTs
