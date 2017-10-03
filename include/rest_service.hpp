#ifndef INCG_CR_REST_SERVICE_HPP
#define INCG_CR_REST_SERVICE_HPP
#include "../include/namespace_aliases.hpp"
#include "../include/http_verb.hpp" // cr::HttpVerb
#include "../include/except.hpp" // cr::NullPointerException
#include <restbed> // restbed::Session, restbed::Resource, restbed::Service, restbed::Settings
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/utility/string_ref.hpp> // boost::string_ref
#include <cstdint> // std::uint16_t
#include <utility> // std::pair
#include <memory> // std::shared_ptr
#include <functional> // std::function
#include <vector> // std::vector

namespace cr
{
/*!
 * \brief A type to publish REST resources.
 * \note Used as the implementation of RestApi.
**/
class RestService
    : private boost::noncopyable
{
public:
    using this_type = RestService;
    using RequestHandler = std::function<void (const std::shared_ptr<rest::Session>)>;

    /*!
     * \brief Creates a RestService object.
    **/
    RestService();

    /*!
     * \brief Destroys a RestService object.
    **/
    ~RestService();

    /*!
     * \brief Adds a REST resource to this RestService.
     * \param path The path to use, e.g. /resource
     * \param httpVerb The HTTP verb to use.
     * \param requestHandler The callback routine for when an 'httpVerb' request
     *                       is sent to 'path'.
     * \return A reference to this object.
    **/
    this_type &addResource(boost::string_ref path,
                           HttpVerb httpVerb,
                           const RequestHandler &requestHandler);

    /*!
     * \brief Brings the resources added online at port 'port'.
     * \param port The port to use.
     * \return A reference to this object.
     * \note Will make the current thread run the REST API, waiting for
     *       requests to come in.
    **/
    this_type &startService(std::uint16_t port);

    /*!
     * \brief Returns the HTTP URI of this RestService as text.
     * \return A textual representation of this RestService's HTTP URI.
     * \throws cr::NullPointerException if the shared_ptr to the HTTP URI
     *         that was fetched is nullptr.
    **/
    std::string getHttpUri() const;

private:
    /*!
     * \brief Implementation function to publish the resources.
     * \note Used in startService.
    **/
    void publishResources();

    rest::Service m_service; /*!< The underlying service */
    std::vector<std::pair<std::shared_ptr<rest::Resource>, RequestHandler>> m_resources;
    std::shared_ptr<rest::Settings> m_settings;
};
} // namespace cr
#endif // INCG_CR_REST_SERVICE_HPP
