#include "../include/example_type.hpp"
#include "../include/json.hpp" // cr::fetchString, cr::fetchDouble, cr::fetchObject, cr::fetchArray
#include <ciso646> // not
#include <utility> // std::move
#include <ostream> // std::ostream
#include <string> // std::string
#include <iterator> // std::back_inserter
#include <algorithm> // std::transform

namespace cr
{
ExampleType::Struct
ExampleType::Struct::fromJson(const json::GenericValue<json::UTF8<>> &object)
{
    const int i{ fetchInt("i", object) };
    const double d{ fetchDouble("d", object) };

    const Struct s{ i, d };
    return s;
}

void
ExampleType::Struct::asJson(json::PrettyWriter<json::StringBuffer> &writer) const
{
    writer.StartObject();

    writer.String("i");
    writer.Int(i);

    writer.String("d");
    writer.Double(d);

    writer.EndObject();
}

ExampleType::ExampleType(std::string s, Struct strct, std::vector<double> v)
    : m_str{ std::move(s) },
      m_struct{ strct },
      m_v{ std::move(v) }
{
}

ExampleType ExampleType::fromJson(const json::Document &jsonDocument)
{
    if (not jsonDocument.IsObject()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "jsonDocument was not a JSON object.");
    }

    const std::string str{ fetchString("str", jsonDocument) };
    const Struct nestedStruct{ Struct::fromJson(fetchObject("struct",
                                                            jsonDocument)) };
    const json::GenericValue<json::UTF8<>>::ConstArray a{
        fetchArray("v", jsonDocument)
    };

    std::vector<double> v{ };

    std::transform(std::begin(a), std::end(a), std::back_inserter(v),
                   [](const json::GenericValue<json::UTF8<>> &e) {
        if (not e.IsDouble()) {
            CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                      "json array contained invalid value.");
        }

        return e.GetDouble();
    });

    return ExampleType{ str, nestedStruct, std::move(v) };
}

void ExampleType::asJson(json::PrettyWriter<json::StringBuffer> &writer) const
{
    writer.StartObject();

    writer.String("str");
    writer.String(m_str.data());

    writer.String("struct");
    m_struct.asJson(writer);

    writer.String("v");
    vecToJson(writer);

    writer.EndObject();
}

void ExampleType::vecToJson(json::PrettyWriter<json::StringBuffer> &writer) const
{
    writer.StartArray();
    for (double d : m_v) {
        writer.Double(d);
    }
    writer.EndArray();
}

std::ostream &operator<<(std::ostream &os, const ExampleType &exampleType)
{
    return os << jsonAsText(asJson(exampleType));
}
} // namespace cr
