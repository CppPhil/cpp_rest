#ifndef INCG_CR_EXAMPLE_REST_API_HPP
#define INCG_CR_EXAMPLE_REST_API_HPP
#include "../include/rest_api.hpp" // cr::RestApi
#include <cstdint> // std::uint16_t

namespace cr
{
class ExampleRestApi
    : public RestApi<ExampleRestApi>
{
public:
    using this_type = ExampleRestApi;
    using base_type = RestApi<this_type>;

    ExampleRestApi();

    ~ExampleRestApi();

    this_type &start(std::uint16_t port);

private:
    void handlePostResource(rest::Session &session);

    void handlePostResource2(rest::Session &session);
};
} // namespace cr
#endif // INCG_CR_EXAMPLE_REST_API_HPP
