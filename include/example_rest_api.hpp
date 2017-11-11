#ifndef INCG_CR_EXAMPLE_REST_API_HPP
#define INCG_CR_EXAMPLE_REST_API_HPP
#include "../include/rest_api.hpp" // cr::RestApi
#include <cstdint> // std::uint16_t
#include <string> // std::string

namespace cr
{
/*!
 * \brief An example REST API type.
**/
class ExampleRestApi
    : public RestApi<ExampleRestApi>
{
public:
    using this_type = ExampleRestApi;
    using base_type = RestApi<this_type>;

    /*!
     * \brief Creates an ExampleRestApi object.
     *        Registers the REST resources with the base type.
     * \param restbedLogFilePath Path to the file that the log of the underlying
     *                           restbed::Service shall be written to.
    **/
    explicit ExampleRestApi(std::string restbedLogFilePath);

    ExampleRestApi(this_type &&other);

    this_type &operator=(this_type &&other);

    /*!
     * \brief Destroys an ExampleRestApi object.
    **/
    ~ExampleRestApi();

    /*!
     * \brief Brings the REST API online at port 'port' running in this thread.
     * \param port The port to bring the REST API online on.
     * \return A reference to this object.
    **/
    this_type &start(std::uint16_t port);

private:
    /*!
     * \brief Callback routine for POSTs to /resource
     * \param session The restbed::Session object.
    **/
    void handlePostResource(rest::Session &session);

    /*!
     * \brief Callback routine for POSTs to /resource2
     * \param session The restbed::Session object.
    **/
    void handlePostResource2(rest::Session &session);
};
} // namespace cr
#endif // INCG_CR_EXAMPLE_REST_API_HPP
