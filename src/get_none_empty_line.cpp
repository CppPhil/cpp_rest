#include "../include/get_none_empty_line.hpp"
#include <ciso646> // not, or
#include <istream> // std::istream
#include <ostream> // std::ostream

namespace cr
{
std::istream &getNoneEmptyLine(
    std::istream &input,
    std::string &str,
    std::ostream &os,
    boost::string_ref prompt,
    boost::string_ref errorPrompt)
{
    str = std::string{ };

    for (bool firstTry{ true }; str.empty() or not input; firstTry = false) {
        input.clear(); // clear errors on the input stream

        if (firstTry) {
            os << prompt;
        } else {
            os << errorPrompt;
        }

        os << ' ';

        std::getline(input, str);
    }

    return input;
}
} // namespace cr
