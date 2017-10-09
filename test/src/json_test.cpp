#include "../../include/json.hpp" // cr::parseJson
#include <doctest.h>

TEST_CASE("parse_json_positive_test")
{
    static constexpr char jsonTxt[]
        = R"(
             {
                 "string": "text",
                 "object": {
                               "integer": 5,
                               "boolean": true
                           },
                 "ary": [1, 2, 3, 4, 5]
             }
          )";

    REQUIRE_NOTHROW(cr::parseJson(jsonTxt));
    cr::json::Document doc{ cr::parseJson(jsonTxt) };

    REQUIRE(doc.HasMember("string"));
    REQUIRE(doc.HasMember("object"));
    REQUIRE(doc.HasMember("ary"));

    REQUIRE(doc["string"].IsString());
    REQUIRE(doc["object"].IsObject());
    REQUIRE(doc["ary"].IsArray());

    const cr::json::GenericValue<cr::json::UTF8<>> &object{
        doc["object"]
    };

    REQUIRE(object.HasMember("integer"));
    REQUIRE(object.HasMember("boolean"));

    REQUIRE(object["integer"].IsInt());
    REQUIRE(object["boolean"].IsBool());

    using ArrayType = cr::json::GenericValue<cr::json::UTF8<>>::Array;

    ArrayType array{ doc["ary"].GetArray() };

    for (decltype(array.Size()) i{ 0U }; i < array.Size(); ++i) {
        REQUIRE(array[i].IsInt());
        REQUIRE(array[i] == (i + 1U));
    }
}
