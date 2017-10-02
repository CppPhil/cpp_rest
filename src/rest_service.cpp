#include "../include/rest_service.hpp"
#include "../include/except.hpp" // CR_THROW_IF_NULL
#include <boost/lexical_cast.hpp> // boost::lexical_cast
#include <string> // std::string

namespace cr
{
RestService::RestService()
    : m_service{ },
      m_resources{ },
      m_settings{ std::make_shared<rest::Settings>() }
{
}

RestService::~RestService() = default;

RestService &RestService::addResource(boost::string_ref path,
                                      HttpVerb httpVerb,
                                      const RequestHandler &requestHandler)
{
    m_resources.emplace_back(std::make_shared<rest::Resource>(),
                             requestHandler);

    auto &pair = m_resources.back();
    rest::Resource &resource{ *(pair.first) };
    const RequestHandler &callback{ pair.second };

    resource.set_path(path.data());
    resource.set_method_handler(boost::lexical_cast<std::string>(httpVerb),
                                callback);

    return *this;
}

RestService &RestService::startService(std::uint16_t port)
{
    m_settings->set_port(port);
    m_settings->set_default_header("Connection", "close");

    publishResources();

    m_service.start(m_settings);

    return *this;
}

std::string RestService::getHttpUri() const
{
    const std::shared_ptr<const rest::Uri> uriPtr{ m_service.get_http_uri() };
    CR_THROW_IF_NULL(uriPtr);
    return uriPtr->to_string();
}

void RestService::publishResources()
{
    for (const auto &pair : m_resources) {
        const std::shared_ptr<rest::Resource> &resource{ pair.first };
        m_service.publish(resource);
    }
}
} // namespace cr
