#include "../include/parse_black_board_message.hpp"
#include "../include/json.hpp" // cr::parseJson
#include <string> // std::string
#include <iterator> // std::begin, std::end

namespace cr
{
std::uint16_t parseBlackBoardMessage(const std::vector<Byte> &blackBoardMessage)
{
    static constexpr char identifier[] = "blackboard_port";

    const std::string messageAsString(
        std::begin(blackBoardMessage),
        std::end(blackBoardMessage)
    );

    const json::Document jsonDocument{ cr::parseJson(messageAsString) };

    return static_cast<std::uint16_t>(fetchUint64(identifier, jsonDocument));
}
} // namespace cr
