/*!
 * \file stringify.hpp
 * \brief Exports the CR_STRINGIFY macro.
**/
#ifndef INCG_CR_STRINGIFY_HPP
#define INCG_CR_STRINGIFY_HPP

/*!
 * \def CR_STRINGIFY_IMPL(a)
 * \brief Implementation macro. Not to be used directly.
**/

/*!
 * \def CR_STRINGIFY(a)
 * \brief Stringifies the tokens 'a'.
 * \example CR_STRINGIFY(hello) expands to "hello".
**/

#define CR_STRINGIFY_IMPL(a) #a

#define CR_STRINGIFY(a) CR_STRINGIFY_IMPL(a)
#endif // INCG_CR_STRINGIFY_HPP
