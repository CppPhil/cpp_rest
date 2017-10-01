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
add_executable(${PROJECT_NAME} "src/main.cpp")

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

if(MSVC)
    include_directories(C:/Libraries/boost_1_64_0)   
    
    target_link_libraries(${PROJECT_NAME} $ENV{HOMEPATH}/restbed/build/librestbed.a)
    include_directories($ENV{HOMEPATH}/restbed/source)

    include_directories($ENV{HOMEPATH}/json/src)

    include_directories($ENV{HOMEPATH}/GSL/include)

    include_directories($ENV{HOMEPATH}/doctest/doctest) 
else()
    target_link_libraries(${PROJECT_NAME} $ENV{HOME}/restbed/build/librestbed.a)
    include_directories($ENV{HOME}/restbed/source)

    include_directories($ENV{HOME}/json/src)

    include_directories($ENV{HOME}/GSL/include)

    include_directories($ENV{HOME}/doctest/doctest)
endif()

enable_testing()

add_executable(tester "test/src/test.cpp")
add_test(Tester tester)

