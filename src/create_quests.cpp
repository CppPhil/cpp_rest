#include "../include/create_quests.hpp"
#include "../include/json.hpp" // cr::parseJson, cr::fetchArray
#include <ciso646> // not
#include <iterator> // std::begin, std::end, std::back_inserter
#include <algorithm> // std::transform

namespace cr
{
std::vector<Quest> createQuests(boost::string_ref jsonText)
{
    static constexpr char arrayName[] = "objects";

    const json::Document jsonDocument{ cr::parseJson(jsonText) };

    if (not jsonDocument.IsObject()) { // It must be a JSON object.
        CR_THROW_WITH_SOURCE_INFO(
            InvalidJsonException,
            "jsonDocument was not a JSON object.");
    }

    const json::GenericValue<json::UTF8<>>::ConstArray array{
        fetchArray(arrayName, jsonDocument)
    };

    std::vector<Quest> retVal{ };

    std::transform(
        std::begin(array),
        std::end(array),
        std::back_inserter(retVal),
        [](const json::GenericValue<json::UTF8<>> &e) {
            if (not e.IsObject()) {
                CR_THROW_WITH_SOURCE_INFO(
                    InvalidJsonException,
                    "json array contained invalid value.");
            }

            return Quest::fromJson(e);
    });

    return retVal;
}
} // namespace cr
