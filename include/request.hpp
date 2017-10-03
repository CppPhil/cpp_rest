/*!
 * \file request.hpp
 * \brief Exports utilities for working with restbed::Requests.
**/
#ifndef INCG_RC_REQUEST_HPP
#define INCG_RC_REQUEST_HPP
#include "../include/namespace_aliases.hpp"
#include <corvusoft/restbed/request.hpp> // restbed::Request
#include <cstddef> // std::size_t

namespace cr
{
/*!
 * \brief Returns the Content-Length of a restbed::Request.
 * \param request The request to get the Content-Length of.
 * \return The Content-Length of 'request' or 0 if the header of 'request'
 *         had no Content-Length in it.
**/
std::size_t getContentLength(const rest::Request &request);
} // namespace cr
#endif // INCG_RC_REQUEST_HPP
