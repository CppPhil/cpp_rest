#ifndef INCG_CR_REST_API_HPP
#define INCG_CR_REST_API_HPP
#include "../include/rest_service.hpp" // cr::RestService
#include <boost/noncopyable.hpp> // boost::noncopyable
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
    using RequestHandler = void (derived_type::*)(rest::Session &);

    /*!
     * \brief Initializes the RestApi base class part.
     * \param derived Pointer to the derived type.
    **/
    explicit RestApi(derived_type *derived)
        : m_restService{ },
          m_derived{ derived }
    {
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
    this_type &registerResource(boost::string_ref path,
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
    **/
    this_type &startRestApi(std::uint16_t port)
    {
        m_restService.startService(port);
        return *this;
    }

    /*!
     * \brief Returns the HTTP URI of the underlying REST service.
     * \return The HTTP URI as std::string.
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
