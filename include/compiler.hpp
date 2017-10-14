/*!
 * \file compiler.hpp
 * \brief Defines macros to determine the compiler and the version of that compiler being used.
**/
#ifndef INCG_CR_COMPILER_HPP
#define INCG_CR_COMPILER_HPP

/*!
 * \def CR_COMPILER_CLANG
 * \brief CR_COMPILER will be defined as this if clang is being used.
**/

/*!
 * \def CR_COMPILER_ICC
 * \brief CR_COMPILER will be defined as this
 *        if Intel C++ Compiler is being used.
**/

/*!
 * \def CR_COMPILER_MSVC
 * \brief CR_COMPILER will be defined as this if Microsoft Visual Compiler is
 *        being used.
**/

/*!
 * \def CR_COMPILER_GCC
 * \brief CR_COMPILER will be defined as this if gcc is being used.
**/

/*!
 * \def CR_COMPILER_UNKNOWN
 * \brief CR_COMPILER will be defined as this if the compiler being used
 *        could not be determined.
**/

/*!
 * \def CR_COMPILER
 * \brief Will be defined as CR_COMPILER_CLANG, CR_COMPILER_ICC,
 *        CR_COMPILER_MSVC, CR_COMPILER_GCC or CR_COMPILER_UNKNOWN
 *        depending on which compiler is being used.
**/

/*!
 * \def CR_COMPILER_MAJOR
 * \brief The major version of the compiler.
**/

/*!
 * \def CR_COMPILER_MINOR
 * \brief The minor version of the compiler.
**/

/*!
 * \def CR_COMPILER_PATCH
 * \brief The patch level of the compiler.
**/

/*!
 * \def CR_COMPILER_VERSION_CHECK(major, minor, patch)
 * \brief Can be used to create a compiler version using a major, minor
 *        and patch number. Useful to compare the current compiler version
 *        to a specific version.
**/

/*!
 * \def CR_COMPILER_VERSION
 * \brief The current compiler version, may be compared to a number generated
 *        with CR_COMPILER_VERSION_CHECK
**/

#define CR_COMPILER_CLANG (0x0004) /* meaningless number */
#define CR_COMPILER_ICC (0x0005) /* meaningless number */
#define CR_COMPILER_MSVC (0x0006) /* meaningless number */
#define CR_COMPILER_GCC (0x0007) /* meaningless number */
#define CR_COMPILER_UNKNOWN (0x0008) /* meaningless number */

#if defined(__clang__)
#   define CR_COMPILER CR_COMPILER_CLANG
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#   define CR_COMPILER CR_COMPILER_ICC
#elif defined(_MSC_VER)
#   define CR_COMPILER CR_COMPILER_MSVC
#elif defined(__GNUC__) || defined(__GNUG__)
#   define CR_COMPILER CR_COMPILER_GCC
#else
#   define CR_COMPILER CR_COMPILER_UNKNOWN
#   warning "Compiler could not be detected"
#endif

#if CR_COMPILER == CR_COMPILER_CLANG
    #define CR_COMPILER_MAJOR __clang_major__
    #define CR_COMPILER_MINOR __clang_minor__
    #define CR_COMPILER_PATCH __clang_patchlevel__
#elif CR_COMPILER == CR_COMPILER_ICC
    #define CR_COMPILER_MAJOR __INTEL_COMPILER / 100
    #define CR_COMPILER_MINOR __INTEL_COMPILER % 100 / 10
    #define CR_COMPILER_PATCH __INTEL_COMPILER % 10
#elif CR_COMPILER == CR_COMPILER_MSVC
    #define CR_COMPILER_MAJOR _MSC_FULL_VER / 10000000
    #define CR_COMPILER_MINOR _MSC_FULL_VER % 10000000 / 100000
    #define CR_COMPILER_PATCH _MSC_FULL_VER % 100000
#elif CR_COMPILER == CR_COMPILER_GCC
    #define CR_COMPILER_MAJOR __GNUC__
    #define CR_COMPILER_MINOR __GNUC_MINOR__
    #define CR_COMPILER_PATCH __GNUC_PATCHLEVEL__
#else
    #define CR_COMPILER_MAJOR (0x00)
    #define CR_COMPILER_MINOR (0x00)
    #define CR_COMPILER_PATCH_VERSION (0x00)
#endif

#define CR_COMPILER_VERSION_CHECK(major, minor, patch) \
    (((major) * 16777216) + ((minor) * 65536) + (patch))

#define CR_COMPILER_VERSION \
    CR_COMPILER_VERSION_CHECK(CR_COMPILER_MAJOR, CR_COMPILER_MINOR, CR_COMPILER_PATCH)

#endif // INCG_CR_COMPILER_HPP
