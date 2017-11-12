#ifndef INCG_CR_SAFE_OPTIONAL_ACCESS_HPP
#define INCG_CR_SAFE_OPTIONAL_ACCESS_HPP
#include "../include/except.hpp" // cr::OptionalHadNoValueException
#include <boost/optional.hpp> // boost::optional
#include <ciso646> // not

namespace cr
{
/*!
 * \brief Safely accesses an optional.
 * \param optional The optional to get the value from.
 * \return The value extracted.
 * \throws OptionalHadNoValueException if 'optional' had no value.
**/
template <typename Ty>
Ty &safeOptionalAccess(boost::optional<Ty> &optional)
{
    if (not optional) {
        CR_THROW_WITH_SOURCE_INFO(
            OptionalHadNoValueException,
            "optional had no value!");
    }

    return *optional;
}

/*!
 * \brief Safely accesses an optional.
 * \param optional The optional to get the value from.
 * \return The value extracted.
 * \throws OptionalHadNoValueException if 'optional' had no value.
**/
template <typename Ty>
const Ty &safeOptionalAccess(const boost::optional<Ty> &optional)
{
    return ::cr::safeOptionalAccess(
        const_cast<boost::optional<Ty> &>(optional));
}
} // namespace cr
#endif // INCG_CR_SAFE_OPTIONAL_ACCESS_HPP
