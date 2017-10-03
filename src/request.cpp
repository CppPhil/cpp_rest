#include "../include/request.hpp"
#include <string> // std::string, std::literals::string_literals::operator""s

namespace cr
{
std::size_t getContentLength(const rest::Request &request)
{
    using namespace std::literals::string_literals;

    // return this value if there is no "Content-Length" in the header.
    static constexpr std::size_t fallbackValue{ 0U };

    return request.get_header("Content-Length"s, fallbackValue);
}
} // namespace cr
