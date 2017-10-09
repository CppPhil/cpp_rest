#include "../include/response.hpp"
#include "../include/json.hpp" // cr::jsonAsText
#include <corvusoft/restbed/response.hpp> // restbed::Response
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <string> // std::string, std::literals::string_literals::operator""s
#include <type_traits> // std::underlying_type_t
#include <iterator> // std::inserter
#include <algorithm> // std::copy

namespace cr
{
std::size_t getContentLength(const rest::Response &response)
{
    static constexpr std::size_t defaultValue{ 0U };
    static constexpr char contentLenStr[] = "Content-Length";

    return response.get_header(contentLenStr, defaultValue);
}

void respond(rest::Session &session,
             HttpStatusCode httpStatusCode,
             const void *replyData,
             std::size_t replyDataByteSize,
             boost::string_ref contentType,
             const std::multimap<std::string, std::string> &headers)
{
    using namespace std::literals::string_literals;

    const auto *begin = static_cast<const unsigned char *>(replyData);
    const auto *end = begin + replyDataByteSize;
    const rest::Bytes reply(begin, end);

    std::multimap<std::string, std::string> headersToSend{
        { "Content-Length"s, boost::lexical_cast<std::string>(replyDataByteSize) },
        { "Content-Type"s, contentType.data() }
    };

    std::copy(std::begin(headers), std::end(headers),
              std::inserter(headersToSend, std::begin(headersToSend)));

    session.close(static_cast<std::underlying_type_t<HttpStatusCode>>(httpStatusCode),
                  reply,
                  headersToSend);
}

void respond(rest::Session &session,
             HttpStatusCode httpStatusCode,
             const json::Document &jsonDocument,
             const std::multimap<std::string, std::string> &headers)
{
    static constexpr char contentType[] = "application/json";

    const std::string jsonString{ jsonAsText(jsonDocument) };

    respond(session, httpStatusCode, jsonString.data(),
            jsonString.size(), contentType, headers);
}

void respond(rest::Session &session,
             HttpStatusCode httpStatusCode,
             boost::string_ref stringToSend,
             const std::multimap<std::string, std::string> &headers)
{
    static constexpr char contentType[] = "text/plain";

    respond(session, httpStatusCode, stringToSend.data(),
            stringToSend.size(), contentType, headers);
}
} // namespace cr
