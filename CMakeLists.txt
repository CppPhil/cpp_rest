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

project(cpp_rest)
add_executable(${PROJECT_NAME} "src/main.cpp" "src/rest_service.cpp" "include/rest_service.hpp" "include/namespace_aliases.hpp" "include/http_verb.hpp" "src/http_verb.cpp" "include/rest_api.hpp" "include/example_rest_api.hpp" "src/example_rest_api.cpp")

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    include_directories(C:/Libraries/boost_1_63_0)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_link_libraries(${PROJECT_NAME} $ENV{USERPROFILE}/restbed/build/Debug/restbed.lib)
    else()
        target_link_libraries(${PROJECT_NAME} $ENV{USERPROFILE}/restbed/build/Release/restbed.lib)
    endif()

    include_directories($ENV{USERPROFILE}/restbed/source)

    include_directories($ENV{USERPROFILE}/rapidjson/include) # C:\Users\appveyor\restbed\build\Debug\restbed.lib

    include_directories($ENV{USERPROFILE}/GSL/include)

    include_directories($ENV{USERPROFILE}/doctest/doctest)
else()
    target_link_libraries(${PROJECT_NAME} $ENV{HOME}/restbed/build/librestbed.a)
    include_directories($ENV{HOME}/restbed/source)

    include_directories($ENV{HOME}/rapidjson/include)

    include_directories($ENV{HOME}/GSL/include)

    include_directories($ENV{HOME}/doctest/doctest)
endif()

enable_testing()

add_executable(tester "test/src/test.cpp")
add_test(Tester tester)

