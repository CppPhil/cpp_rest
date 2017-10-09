/*!
 * \file json.hpp
 * \brief Exports JSON conversion utilities.
**/
#ifndef INCG_CR_JSON_HPP
#define INCG_CR_JSON_HPP
#include "../include/namespace_aliases.hpp"
#include <rapidjson/document.h> // rapidjson::Document
#include <rapidjson/prettywriter.h> // rapidjson::PrettyWriter
#include <rapidjson/stringbuffer.h> // rapidjson::StringBuffer
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstdint> // std::uint64_t, std::int64_t
#include <string> // std::string

namespace cr
{
/*!
 * \brief Creates a JSON document from JSON text.
 * \param jsonText The JSON text to be parsed.
 * \return The resulting JSON document.
 * \throws FailedToParseJsonException if the JSON text passed in is invalid.
**/
json::Document parseJson(boost::string_ref jsonText);

/*!
 * \brief Converts a JSON document to JSON text.
 * \param jsonDocument The JSON document to convert.
 * \return The JSON text corresponding to 'jsonDocument'.
**/
std::string jsonAsText(const json::Document &jsonDocument);

/*!
 * \brief Converts an object to a JSON document.
 * \param ty The object to convert to a JSON document.
 * \return The resulting JSON document.
 * \note calls .asJson on 'ty' passing a
 *       rapidjson::PrettyWriter<rapidjson::StringBuffer>.
 * \throws FailedToParseJsonException if the resulting JSON could not be parsed.
**/
template <typename Ty>
json::Document asJson(const Ty &ty)
{
    json::StringBuffer sb{ };
    json::PrettyWriter<json::StringBuffer> writer{ sb };

    ty.asJson(writer);

    return parseJson(sb.GetString());
}

/*!
 * \brief Converts a JSON document to an object of type 'Ty'.
 * \param jsonDocument The JSON document to convert.
 * \return The resulting object.
 * \note Calls the static member function fromJson of type 'Ty' passing a
 *       rapidjson::Document.
 * \throws cr::InvalidJsonException if the JSON given was invalid.
**/
template <typename Ty>
Ty fromJson(const json::Document &jsonDocument)
{
    return Ty::fromJson(jsonDocument);
}

/*!
 * \brief Fetches a JSON Array from a JSON object.
 * \param identifier The key of the JSON Array value to fetch.
 * \param json The JSON object to fetch the JSON Array from.
 * \return The JSON Array extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a JSON Array.
**/
json::GenericValue<json::UTF8<>>::Array fetchArray(
    boost::string_ref identifier,
    json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a JSON Array from a JSON object.
 * \param identifier The key of the JSON Array value to fetch.
 * \param json The JSON object to fetch the JSON Array from.
 * \return The JSON Array extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a JSON Array.
**/
json::GenericValue<json::UTF8<>>::ConstArray fetchArray(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a bool from a JSON object.
 * \param identifier The key of the bool value to fetch.
 * \param json The JSON object to fetch the bool from.
 * \return The bool extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a bool.
**/
bool fetchBool(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a double from a JSON object.
 * \param identifier The key of the double value to fetch.
 * \param json The JSON object to fetch the double from.
 * \return The double extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a double.
**/
double fetchDouble(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a float from a JSON object.
 * \param identifier The key of the float value to fetch.
 * \param json The JSON object to fetch the float from.
 * \return The float extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a float.
**/
float fetchFloat(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches an int from a JSON object.
 * \param identifier The key of the int value to fetch.
 * \param json The JSON object to fetch the int from.
 * \return The int value extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not an int.
**/
int fetchInt(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a std::int64_t from a JSON object.
 * \param identifier The key of the std::int64_t value to fetch.
 * \param json The JSON object to fetch the std::int64_t from.
 * \return The std::int64_t extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a std::int64_t.
**/
std::int64_t fetchInt64(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a JSON Object from a JSON object.
 * \param identifier The key of the JSON Object value to fetch.
 * \param json The JSON object to fetch the JSON Object value from.
 * \return The JSON Object extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a JSON Object.
**/
json::GenericValue<json::UTF8<>> &fetchObject(
    boost::string_ref identifier,
    json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a JSON Object from a JSON object.
 * \param identifier The key of the JSON Object value to fetch.
 * \param json The JSON object to fetch the JSON Object value from.
 * \return The JSON Object extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a JSON Object.
**/
const json::GenericValue<json::UTF8<>> &fetchObject(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a string from a JSON object.
 * \param identifier The key of the string value to fetch.
 * \param json The JSON object to fetch the string from.
 * \return The string extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a string.
**/
std::string fetchString(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches an unsigned int from a JSON object.
 * \param identifier The key of the unsigned int value to fetch.
 * \param json The JSON object to fetch the unsigned int from.
 * \return The unsigned int extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not an unsigned int.
**/
unsigned fetchUint(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);

/*!
 * \brief Fetches a std::uint64_t from a JSON object.
 * \param identifier The key of the std::uint64_t value to fetch.
 * \param json The JSON object to fetch the std::uint64_t from.
 * \return The std::uint64_t extracted.
 * \throws cr::InvalidJsonException if 'json' does not contain
 *         a member called 'identifier' or the associated value
 *         is not a std::uint64_t.
**/
std::uint64_t fetchUint64(
    boost::string_ref identifier,
    const json::GenericValue<json::UTF8<>> &json);
} // namespace cr
#endif // INCG_CR_JSON_HPP
