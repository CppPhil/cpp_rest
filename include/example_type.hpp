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
class ExampleType
{
public:
    using this_type = ExampleType;

    struct Struct
    {
        int i;
        double d;

        static Struct fromJson(const json::GenericValue<json::UTF8<>> &object);

        void asJson(json::PrettyWriter<json::StringBuffer> &writer) const;
    };

    ExampleType(std::string s, Struct strct, std::vector<double> v);

    static ExampleType fromJson(const json::Document &jsonDocument);

    void asJson(json::PrettyWriter<json::StringBuffer> &writer) const;

private:
    void vecToJson(json::PrettyWriter<json::StringBuffer> &writer) const;

    friend std::ostream &operator<<(std::ostream &os,
                                    const ExampleType &exampleType);

    std::string m_str;
    Struct m_struct;
    std::vector<double> m_v;
};
} // namespace cr
#endif // INCG_CR_EXAMPLE_TYPE_HPP
