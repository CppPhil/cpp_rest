#ifndef INCG_CR_NONCOPYABLE_HPP
#define INCG_CR_NONCOPYABLE_HPP

/*!
 * \def CR_NONCOPYABLE(typeIdentifier)
 * \brief Macro to be placed in the public section of a type.
 *        Pass the identifier of the type into this macro.
 *        Used to declare a type as noncopyable.
**/

#define CR_NONCOPYABLE(typeIdentifier) \
    typeIdentifier(const typeIdentifier &) = delete; \
    typeIdentifier &operator=(const typeIdentifier &) = delete    

#endif // INCG_CR_NONCOPYABLE_HPP

