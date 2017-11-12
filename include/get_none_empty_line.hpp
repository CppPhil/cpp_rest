#ifndef INCG_CR_GET_NONE_EMPTY_LINE_HPP
#define INCG_CR_GET_NONE_EMPTY_LINE_HPP
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <iosfwd> // std::istream, std::ostream
#include <string> // std::string

namespace cr
{
std::istream &getNoneEmptyLine(
    std::istream &input,
    std::string &str,
    std::ostream &os,
    boost::string_ref prompt,
    boost::string_ref errorPrompt = "Try again:");
} // namespace cr
#endif // INCG_CR_GET_NONE_EMPTY_LINE_HPP
