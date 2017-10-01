#ifndef INCG_CR_HTTP_VERB_HPP
#define INCG_CR_HTTP_VERB_HPP
#include <iosfwd> // std::ostream

namespace cr
{
/*!
 * \brief Enum for all the possible HTTP verbs.
**/
enum class HttpVerb
{
    GET,
    POST,
    PUT,
    PATCH,
    DELETE,
    COPY,
    HEAD,
    OPTIONS,
    LINK,
    UNLINK,
    PURGE,
    LOCK,
    UNLOCK,
    PROPFIND,
    VIEW,
    CONNECT,
    TRACE
};

/*!
 * \brief Prints a textual representation of 'httpVerb' to 'os'.
 * \param os The ostream to print to.
 * \param httpVerb The HTTP verb to print.
 * \return A reference to 'os'.
 * \note Using boost::lexical_cast<std::string> this function can be used
 *       to convert an HttpVerb object to a std::string.
**/
std::ostream &operator<<(std::ostream &os, HttpVerb httpVerb);
} // namespace cr
#endif // INCG_CR_HTTP_VERB_HPP
