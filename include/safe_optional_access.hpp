#ifndef INCG_CR_SAFE_OPTIONAL_ACCESS_HPP
#define INCG_CR_SAFE_OPTIONAL_ACCESS_HPP
#include "../include/except.hpp" // cr::OptionalHadNoValueException
#include <boost/optional.hpp> // boost::optional
#include <ciso646> // not

namespace cr
{
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

template <typename Ty>
const Ty &safeOptionalAccess(const boost::optional<Ty> &optional)
{
    return ::cr::safeOptionalAccess(
        const_cast<boost::optional<Ty> &>(optional));
}
} // namespace cr
#endif // INCG_CR_SAFE_OPTIONAL_ACCESS_HPP
