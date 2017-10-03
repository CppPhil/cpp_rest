#include "../include/json.hpp"
#include "../include/except.hpp" // CR_THROW_WITH_SOURCE_INFO, cr::FailedToParseJsonException, cr::InvalidJsonException
#include <rapidjson/stringbuffer.h> // rapidjson::StringBuffer
#include <rapidjson/prettywriter.h> // rapidjson::PrettyWriter
#include <ciso646> // not

namespace cr
{
json::Document parseJson(boost::string_ref jsonText)
{
    json::Document document{ };

    // Parse the string into the document if possible,
    // otherwise throw an exception.
    if (document.Parse(jsonText.data()).HasParseError()) {
        CR_THROW_WITH_SOURCE_INFO(FailedToParseJsonException,
                                  std::string{ jsonText.data() } + " was invalid");
    }

    return document;
}

std::string jsonAsText(const json::Document &jsonDocument)
{
    // Convert the JSON document to a string.

    json::StringBuffer sb{ };
    json::PrettyWriter<json::StringBuffer> writer{ sb };
    jsonDocument.Accept(writer);

    return std::string{ sb.GetString() };
}

namespace
{
/*!
 * \brief Throws cr::InvalidJsonException if the JSON 'json' does not contain
 *        the member 'identifier'.
 * \param json The JSON to check.
 * \param identifier The member to check for.
 * \throws cr::InvalidJsonException if 'json' does not have a member named
 *         'identifier'.
**/
void ensureJsonHasMember(const json::GenericValue<json::UTF8<>> &json,
                         boost::string_ref identifier)
{
    using namespace std::literals::string_literals;

    // Throw if the JSON does not have the member.
    if (not json.HasMember(identifier.data())) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " did not exist in json");
    }
}
} // anonymous namespace

json::GenericValue<json::UTF8<>>::Array
fetchArray(boost::string_ref identifier,
           json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsArray()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not an array");
    }

    return json[identifier.data()].GetArray();
}

json::GenericValue<json::UTF8<>>::ConstArray
fetchArray(boost::string_ref identifier,
           const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsArray()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not an array");
    }

    return json[identifier.data()].GetArray();
}

bool
fetchBool(boost::string_ref identifier,
          const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsBool()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not bool");
    }

    return json[identifier.data()].GetBool();
}

double
fetchDouble(boost::string_ref identifier,
            const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsDouble()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not double");
    }

    return json[identifier.data()].GetDouble();
}

float
fetchFloat(boost::string_ref identifier,
           const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsFloat()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not float");
    }

    return json[identifier.data()].GetFloat();
}

int
fetchInt(boost::string_ref identifier,
         const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsInt()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not int");
    }

    return json[identifier.data()].GetInt();
}

std::int64_t
fetchInt64(boost::string_ref identifier,
           const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsInt64()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not std::int64_t");
    }

    return json[identifier.data()].GetInt64();
}

json::GenericValue<json::UTF8<>> &
fetchObject(boost::string_ref identifier,
            json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsObject()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not Object");
    }

    return json[identifier.data()];
}

const json::GenericValue<json::UTF8<>> &
fetchObject(boost::string_ref identifier,
            const json::GenericValue<json::UTF8<>> &json)
{
    return fetchObject(identifier,
                       const_cast<json::GenericValue<json::UTF8<>> &>(json));
}

std::string
fetchString(boost::string_ref identifier,
            const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsString()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not String");
    }

    // make a std::string out of the C-Style String.
    return std::string{ json[identifier.data()].GetString() };
}

unsigned
fetchUint(boost::string_ref identifier,
          const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsUint()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not unsigned int");
    }

    return json[identifier.data()].GetUint();
}

std::uint64_t
fetchUint64(boost::string_ref identifier,
            const json::GenericValue<json::UTF8<>> &json)
{
    using namespace std::literals::string_literals;

    ensureJsonHasMember(json, identifier);

    if (not json[identifier.data()].IsUint64()) {
        CR_THROW_WITH_SOURCE_INFO(InvalidJsonException,
                                  "member "s + identifier.data()
                                  + " was not std::uint64_t");
    }

    return json[identifier.data()].GetUint64();
}
} // namespace cr
