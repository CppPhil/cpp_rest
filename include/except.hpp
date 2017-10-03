/*!
 * \file except.hpp
 * \brief This header defines various utilities for working with exceptions.
**/
#ifndef INCG_CR_EXCEPT_HPP
#define INCG_CR_EXCEPT_HPP
#include "../include/stringify.hpp" // CR_STRINGIFY
#include <boost/current_function.hpp> // BOOST_CURRENT_FUNCTION
#include <string> // std::string
#include <stdexcept> // std::runtime_error, std::logic_error

/*!
 * \def CR_DEFINE_EXCEPTION_TYPE(exceptionTypeIdentifier, baseClass)
 * \brief Defines an exception type. Its name will be exceptionTypeIdentifier
 *        and the base class will be baseClass. The exception type is defined
 *        in the current namespace. This macro makes defining new exception
 *        types a lot more convenient by generating a lot of boilerplate code.
**/

/*!
 * \def CR_THROW_WITH_SOURCE_INFO(exceptionType, message)
 * \brief Throws an exception of type exceptionType with the message message
 *        including information regarding where the exception was thrown.
 * \note Note that the line number may have been manipulated using #line.
 *
 * Includes the file, line and function from where the exception was thrown
 * in the message of the exception object of type exceptionType that can be
 * accessed via the .what() member function. The first parameter of this macro
 * must be an exception type, that type will be the type of the exception
 * thrown by the macro. The second parameter of the macro is the message
 * of the user to include in the exception object's message, std::string must
 * be constructible from message.
**/

/*!
 * \def CR_THROW_IF_NULL(pointer)
 * \brief Throws cr::NullPointerException if the pointer passed in is null.
 * \note Uses CR_THROW_WITH_SOURCE_INFO internally.
 * \see CR_THROW_WITH_SOURCE_INFO
**/

#define CR_DEFINE_EXCEPTION_TYPE(exceptionTypeIdentifier, baseClass) \
    class exceptionTypeIdentifier \
        : public baseClass \
    { \
    public: \
        using this_type = exceptionTypeIdentifier; \
        using base_type = baseClass; \
        \
        explicit exceptionTypeIdentifier(const std::string &what_arg) \
            : base_type{ what_arg } \
        { \
        } \
        \
        explicit exceptionTypeIdentifier(const char *what_arg) \
            : base_type{ what_arg } \
        { \
        } \
        \
    }

#define CR_THROW_WITH_SOURCE_INFO(exceptionType, message) \
    throw exceptionType{ \
        "Message: " \
        + std::string{ message } \
        + "\nexception was thrown at:" \
          "\nfile: " __FILE__ \
          "\nline: " CR_STRINGIFY(__LINE__) \
          "\nfunction: " \
        + std::string{ BOOST_CURRENT_FUNCTION } \
    }

#define CR_THROW_IF_NULL(pointer) \
    do { \
        if ((pointer) == nullptr) { \
            CR_THROW_WITH_SOURCE_INFO(cr::NullPointerException, \
                                      CR_STRINGIFY(pointer) " was null!"); \
        } \
    } while (static_cast<void>(0), 0) /* avoid compiler warnings */

namespace cr
{
CR_DEFINE_EXCEPTION_TYPE(NullPointerException, std::runtime_error);
CR_DEFINE_EXCEPTION_TYPE(InvalidEnumeratorValueException, std::logic_error);
CR_DEFINE_EXCEPTION_TYPE(FailedToParseJsonException, std::runtime_error);
CR_DEFINE_EXCEPTION_TYPE(InvalidJsonException, std::runtime_error);
} // namespace cr
#endif // INCG_CR_EXCEPT_HPP
