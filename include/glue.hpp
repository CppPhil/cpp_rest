/*!
 * \file glue.hpp
 * \brief Exports the CR_GLUE macro.
**/
#ifndef INCG_CR_GLUE_HPP
#define INCG_CR_GLUE_HPP

/*!
 * \def CR_GLUE_IMPL(a, b)
 * \brief Implementation macro. Not to be used directly.
**/

/*!
 * \def CR_GLUE(a, b)
 * \brief Token pastes 'a' with 'b'.
 * \example CR_GLUE(hello, world) expands to helloworld.
**/

#define CR_GLUE_IMPL(a, b) a##b

#define CR_GLUE(a, b) CL_GLUE_IMPL(a, b)
#endif // INCG_CR_GLUE_HPP
