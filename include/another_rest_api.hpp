#ifndef INCG_CR_ANOTHER_REST_API_HPP
#define INCG_CR_ANOTHER_REST_API_HPP
#include "namespace_aliases.hpp"
#include "../include/rest_api.hpp" // cr::RestApi
#include <corvusoft/restbed/session.hpp> // restbed::Session
#include <cstdint> // std::uint16_t
#include <string> // std::string

namespace cr
{
/*!
 * \brief Example REST API type that demonstrates the usage of various kinds
 *        of REST parameters.
**/
class AnotherRestApi
    : public RestApi<AnotherRestApi>
{
public:
    using this_type = AnotherRestApi;
    using base_type = RestApi<this_type>;

    /*!
     * \brief Creates an AnotherRestApi object.
     *        Registers the REST resources of this type.
     * \param restbedLogfilePath The file path to the restbed log of
     *                           this REST API.
    **/
    explicit AnotherRestApi(std::string restbedLogfilePath);

    AnotherRestApi(this_type &&other);

    this_type &operator=(this_type &&other);

    /*!
     * \brief Destroys an object of type AnotherRestApi.
    **/
    ~AnotherRestApi();

    /*!
     * \brief start Brings this REST API and its REST resources online.
     * \param port The port to bring the REST API online on.
     * \return A reference to this object.
    **/
    this_type &start(std::uint16_t port);

private:
    /*!
     * \brief Callback routine that handles GET requests to the path param
     *        resource.
     * \param session The associated restbed Session.
    **/
    void handleGetPathParamResource(rest::Session &session);

    /*!
     * \brief Callback routine that handles GET requests to the query param
     *        resource.
     * \param session The associated restbed Session.
    **/
    void handleGetQueryParamResource(rest::Session &session);

    /*!
     * \brief Callback routine that handles LINK requests to the header param
     *        resource.
     * \param session The associated restbed Session.
    **/
    void handleLinkHeaderParamResource(rest::Session &session);
};
} // namespace cr
#endif // INCG_CR_ANOTHER_REST_API_HPP
