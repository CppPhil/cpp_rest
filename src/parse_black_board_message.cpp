#include "../include/parse_black_board_message.hpp"
#include "../include/json.hpp" // cr::parseJson
#include <string> // std::string
#include <iterator> // std::begin, std::end

namespace cr
{
std::uint16_t parseBlackBoardMessage(const std::vector<Byte> &blackBoardMessage)
{
    // the name of the JSON value in the BlackBoard message.
    static constexpr char identifier[] = "blackboard_port";

    // reinterpret the data as a string (since it is a string).
    const std::string messageAsString(
        std::begin(blackBoardMessage),
        std::end(blackBoardMessage)
    );

    // parse the JSON.
    const json::Document jsonDocument{ cr::parseJson(messageAsString) };

    // get the port from it.
    return static_cast<std::uint16_t>(fetchUint64(identifier, jsonDocument));
}
} // namespace cr
