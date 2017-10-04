cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter")
endif()

if(WIN32)
    set(HOMEDIR $ENV{USERPROFILE})
else()
    set(HOMEDIR $ENV{HOME})
endif()

set(UNIT_TEST_NAME unittest)

set(APPLICATION_HEADER_FILES include/rest_service.hpp include/namespace_aliases.hpp include/http_verb.hpp include/rest_api.hpp include/example_rest_api.hpp include/json.hpp include/except.hpp include/glue.hpp include/stringify.hpp include/example_type.hpp include/http_status_code.hpp include/request.hpp include/response.hpp)

set(APPLICATION_SOURCE_FILES src/rest_service.cpp src/http_verb.cpp src/example_rest_api.cpp src/json.cpp src/example_type.cpp src/http_status_code.cpp src/request.cpp src/response.cpp)

set(UNIT_TEST_SOURCE_FILES test/src/main.cpp test/src/json_test.cpp test/src/example_rest_api_test.cpp)

project(cpp_rest)
add_executable(${PROJECT_NAME} "${APPLICATION_HEADER_FILES}" "${APPLICATION_SOURCE_FILES}" "src/main.cpp")

enable_testing()

add_executable(${UNIT_TEST_NAME} "${UNIT_TEST_SOURCE_FILES}" "${APPLICATION_HEADER_FILES}" "${APPLICATION_SOURCE_FILES}")
add_test(Unittest ${UNIT_TEST_NAME})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${UNIT_TEST_NAME} Threads::Threads)

if(WIN32)
    if(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    endif()

    include_directories(C:/Libraries/boost_1_63_0)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/Debug/restbed.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/Debug/restbed.lib)
    else()
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/Release/restbed.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/Release/restbed.lib)
    endif()
else()
    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/librestbed.a)
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/librestbed.a)
endif()

include_directories(${HOMEDIR}/restbed/source)

include_directories(${HOMEDIR}/rapidjson/include)

include_directories(${HOMEDIR}/GSL/include)

include_directories(${HOMEDIR}/doctest/doctest)
