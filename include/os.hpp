/*!
 * \file os.hpp
 * \brief defines macros to detect the operating system used.
**/
#ifndef INCG_CR_OS_HPP
#define INCG_CR_OS_HPP
/*!
 * \def CR_OS_WINDOWS
 * \brief CR_OS will be defined as this if the operating system used is
 *        Microsoft Windows.
**/

/*!
 * \def CR_OS_MAC
 * \brief CR_OS will be defined as this if the operating system used is
 *        Apple Macintosh.
**/

/*!
 * \def CR_OS_LINUX
 * \brief CR_OS will be defined as this if the operating system used is
 *        GNU/Linux
 * \note Everything running a linux kernel will be considered linux.
**/

/*!
 * \def CR_OS_UNKNOWN
 * \brief CR_OS will be defined as this if the operating system used
 *        could not be determined.
**/

/*!
 * \def CR_OS
 * \brief Will be defined as CR_OS_WINDOWS, CR_OS_MAC, CR_OS_LINUX or
 *        CR_OS_UNKNOWN
**/

#define CR_OS_WINDOWS (0x0000) /* meaningless number */
#define CR_OS_MAC (0x0001) /* meaningless number */
#define CR_OS_LINUX (0x0002) /* meaningless number */
#define CR_OS_UNKNOWN (0x0003) /* meaningless number */

#if defined(_WIN32)
#   define CR_OS CR_OS_WINDOWS
#elif defined(__APPLE__)
#   define CR_OS CR_OS_MAC
#elif defined(__linux__)
#   define CR_OS CR_OS_LINUX
#else
#   define CR_OS CR_OS_UNKNOWN
#   warning "Operating system could not be detected"
#endif
#endif // INCG_CR_OS_HPP
