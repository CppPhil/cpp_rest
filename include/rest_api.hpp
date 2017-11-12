#ifndef INCG_CR_REST_API_HPP
#define INCG_CR_REST_API_HPP
#include "../include/rest_service.hpp" // cr::RestService
#include "../include/except.hpp" // CR_THROW_IF_NULL
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <string> // std::string
#include <utility> // std::move

namespace cr
{
/*!
 * \brief CRTP base class for defining REST APIs.
**/
template <typename Derived>
class RestApi
    : private boost::noncopyable
{
public:
    using this_type = RestApi;
    using derived_type = Derived;

    /*!
     * \brief Pointer to a member function of 'derived_type' that returns void
     *        and has a restbed::Session & parameter.
    **/
    using RequestHandler = void (derived_type::*)(rest::Session &);

    /*!
     * \brief Initializes the RestApi base class part.
     * \param derived Pointer to the derived type.
     * \param restbedLogFilePath The path to the restbed log file to write to.
     * \param bindAddress The IPv4 or IPv6 address to have the underlying
     *                    REST service listen on. Defaults to the IPv4 localhost
     *                    address.
     * \throws cr::NullPointerException if 'derived' is nullptr.
    **/
    RestApi(
        derived_type *derived,
        std::string restbedLogFilePath,
        std::string bindAddress = "127.0.0.1")
        : m_restService{ std::move(restbedLogFilePath), std::move(bindAddress) },
          m_derived{ derived }
    {
        CR_THROW_IF_NULL(m_derived); // derived can't be nullptr.
    }

    /*!
     * \brief Move constructor.
     * \param other Reference to the rvalue to move construct from.
    **/
    RestApi(this_type &&other)
        : m_restService{ std::move(other.m_restService) },
          m_derived{ std::move(other.m_derived) }
    {
    }

    /*!
     * \brief Move assignment operator.
     * \param other Reference to the rvalue to move assign with.
     * \return A reference to this object.
    **/
    this_type &operator=(this_type &&other)
    {
        m_restService = std::move(other.m_restService);
        m_derived     = std::move(other.m_derived);
        return *this;
    }

    /*!
     * \brief Shuts down the RestApi.
     * \return A reference to this object.
    **/
    this_type &stop()
    {
        m_restService.stop();
        return *this;
    }

protected:
    /*!
     * \brief Registers a resource with the underlying REST service.
     * \param path The path to use for the resource, e.g. /resource
     * \param httpVerb The HTTP verb to use.
     * \param requestHandler Pointer to a member function of the derived type
     *                       that will take a restbed::Session &.
     * \return A reference to this object.
    **/
    this_type &registerResource(
        boost::string_ref path,
        HttpVerb httpVerb,
        RequestHandler requestHandler)
    {
        auto callback // lambda that will be called by the RestService.
            = [requestHandler, this](const std::shared_ptr<rest::Session> session) {
            (m_derived->*requestHandler)(*session); // forward to the derived's member function
        };

        // register the resource.
        m_restService.addResource(path, httpVerb, std::move(callback));
        return *this;
    }

    /*!
     * \brief Brings the REST API online on port 'port' with the REST resources
     *        registered.
     * \param port The port to use.
     * \return A reference to this object.
     * \note This thread will start running the REST API and will begin waiting
     *       for requests.
    **/
    this_type &startRestApi(std::uint16_t port)
    {
        m_restService.startService(port);
        return *this;
    }

    /*!
     * \brief Returns the HTTP URI of the underlying REST service.
     * \return The HTTP URI as std::string.
     * \throws cr::NullPointerException if the shared_ptr to the HTTP URI
     *         fetched was nullptr.
    **/
    std::string getHttpUri() const
    {
        return m_restService.getHttpUri();
    }

private:
    RestService m_restService; /*!< The underlying RestService */
    derived_type *m_derived; /*!< Pointer to the derived object */
};
} // namespace cr
#endif // INCG_CR_REST_API_HPP
