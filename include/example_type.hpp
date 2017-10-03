#ifndef INCG_CR_EXAMPLE_TYPE_HPP
#define INCG_CR_EXAMPLE_TYPE_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/except.hpp" // CR_THROW_WITH_SOURCE_INFO, cr::InvalidJsonException
#include <rapidjson/document.h> // rapidjson::Document
#include <rapidjson/stringbuffer.h> // rapidjson::StringBuffer
#include <rapidjson/prettywriter.h> // rapidjson::PrettyWriter
#include <iosfwd> // std::ostream
#include <string> // std::string
#include <vector> // std::vector

namespace cr
{
/*!
 * \brief An example type that can be serialized to JSON and be
 *        deserialized from JSON.
**/
class ExampleType
{
public:
    using this_type = ExampleType;

    /*!
     * \brief The type of the nested structure member of ExampleType.
    **/
    struct Struct
    {
        int i; /*!< An integer */
        double d; /*!< A double */

        /*!
         * \brief Creates a Struct type from a rapidjson Object.
         * \param object The rapidjson Object to create a Struct from.
         * \return The Struct created.
        **/
        static Struct fromJson(const json::GenericValue<json::UTF8<>> &object);

        /*!
         * \brief Serializes a Struct to JSON.
         * \param writer The rapidjson writer to write to.
        **/
        void asJson(json::PrettyWriter<json::StringBuffer> &writer) const;
    };

    /*!
     * \brief Creates an object of type ExampleType.
     * \param s The string to use.
     * \param strct The Struct to use.
     * \param v The vector of doubles to use.
    **/
    ExampleType(std::string s, Struct strct, std::vector<double> v);

    /*!
     * \brief Creates an ExampleType object from a rapidjson Document.
     * \param jsonDocument The rapidjson Document to create an ExampleType from.
     * \return The ExampleType created.
    **/
    static ExampleType fromJson(const json::Document &jsonDocument);

    /*!
     * \brief Serializes this ExampleType to JSON.
     * \param writer The rapidjson writer to write to.
    **/
    void asJson(json::PrettyWriter<json::StringBuffer> &writer) const;

private:
    /*!
     * \brief Helper routine to serialize the vector non static data member
     *        as a JSON Array.
     * \param writer The rapidjson writer to write to.
    **/
    void vecToJson(json::PrettyWriter<json::StringBuffer> &writer) const;

    /*!
     * \brief Prints an ExampleType object as JSON.
     * \param os The ostream to print to.
     * \param exampleType The object to print.
     * \return A reference to 'os'.
    **/
    friend std::ostream &operator<<(std::ostream &os,
                                    const ExampleType &exampleType);

    std::string m_str; /*!< The string */
    Struct m_struct; /*!< The nested structure (serialized as JSON Object) */
    std::vector<double> m_v; /*!< The vector<double> (serialized as JSON Array) */
};
} // namespace cr
#endif // INCG_CR_EXAMPLE_TYPE_HPP
