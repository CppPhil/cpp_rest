#ifndef INCG_CR_ANOTHER_REST_API_HPP
#define INCG_CR_ANOTHER_REST_API_HPP
#include "namespace_aliases.hpp"
#include "../include/rest_api.hpp" // cr::RestApi
#include <corvusoft/restbed/session.hpp> // restbed::Session
#include <cstdint> // std::uint16_t
#include <string> // std::string

namespace cr
{
class AnotherRestApi
    : public RestApi<AnotherRestApi>
{
public:
    using this_type = AnotherRestApi;
    using base_type = RestApi<this_type>;

    explicit AnotherRestApi(std::string restbedLogfilePath);

    ~AnotherRestApi();

    this_type &start(std::uint16_t port);

private:
    void handleGetPathParamResource(rest::Session &session);

    void handleGetQueryParamResource(rest::Session &session);
};
} // namespace cr
#endif // INCG_CR_ANOTHER_REST_API_HPP
