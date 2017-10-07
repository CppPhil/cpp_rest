#ifndef INCG_CR_UNUSED_HPP
#define INCG_CR_UNUSED_HPP

/*!
 * \def CR_UNUSED(arg)
 * \brief Macro that can be used to mark something as unused.
 *        Useful to suppress compiler warnings about unused parameters.
**/

#define CR_UNUSED(arg) static_cast<void>((arg))
#endif // INCG_CR_UNUSED_HPP

