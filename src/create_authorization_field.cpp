#include "../include/create_authorization_field.hpp"
#include "../include/log.hpp" // CR_LOG
#include <boost/archive/iterators/base64_from_binary.hpp> // boost::archive::iterators::base64_from_binary
#include <boost/archive/iterators/transform_width.hpp> // boost::archive::iterators::transform_width
#include <boost/archive/iterators/ostream_iterator.hpp> // boost::archive::iterators::ostream_iterator
#include <climits> // CHAR_BIT
#include <sstream> // std::ostringstream
#include <algorithm> // std::copy

namespace cr
{
namespace
{
std::string joinWithColon(
    boost::string_ref userName,
    boost::string_ref passWord)
{
    std::string retVal{ userName.data() };
    retVal.push_back(':');
    retVal += passWord.data();
    return retVal;
}

std::string toBase64(boost::string_ref input)
{
    namespace ait = boost::archive::iterators;
    static constexpr int base64Bits     =  6;
    static constexpr int byteBits       =  8;

    static_assert(byteBits == CHAR_BIT, "Bytes are not 8 bits!");

    using Base64 = ait::base64_from_binary<
        ait::transform_width<const char *, base64Bits, byteBits>>;

    std::ostringstream os{ };

    std::copy(
        Base64{ input.data() },
        Base64{ input.data() + input.size() },
        ait::ostream_iterator<char>(os));

    return os.str();
}
} // anonymous namespace

std::string createAuthorizationField(
    boost::string_ref userName,
    boost::string_ref passWord)
{
    const std::string withColon{ joinWithColon(userName, passWord) };
    const std::string asBase64{ toBase64(withColon) };
    const std::string retVal{ "Basic " + asBase64 };

    CR_LOG(LogLevel::debug)
        << "UserName: "  << userName  << ", PassWord: " << passWord << '\n'
        << "withColon: " << withColon << '\n'
        << "retVal: "    << retVal;

    return retVal;
}
} // namespace cr
