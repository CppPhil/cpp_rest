# GENERAL
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# warning flags
if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter")
endif()

# home directory
if(WIN32)
    set(HOMEDIR $ENV{USERPROFILE})
else()
    set(HOMEDIR $ENV{HOME})
endif()

# declare project
project(cpp_rest)

# STATICALLY LINKED LIBRARY
set(LIBRARY_NAME cpp_rest_lib)

file(GLOB LIB_HEADERS
     include/*.hpp)
     
file(GLOB LIB_SOURCES
     src/*.cpp)
     
add_library(${LIBRARY_NAME} STATIC "${LIB_HEADERS}" "${LIB_SOURCES}")

# find Threads package
find_package(Threads REQUIRED)

target_link_libraries(${LIBRARY_NAME} Threads::Threads)

# APPLICATION
file(GLOB APPLICATION_SOURCE_FILES
     ./*.cpp)

add_executable(${PROJECT_NAME} "${LIB_HEADERS}" "${APPLICATION_SOURCE_FILES}")
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME})

# TEST
set(UNIT_TEST_NAME unittest)

file(GLOB UNIT_TEST_SOURCE_FILES
     test/src/*.cpp)

enable_testing()

add_executable(${UNIT_TEST_NAME} "${LIB_HEADERS}" "${UNIT_TEST_SOURCE_FILES}")
add_test(Unittest ${UNIT_TEST_NAME})
target_link_libraries(${UNIT_TEST_NAME} Threads::Threads)
target_link_libraries(${UNIT_TEST_NAME} ${LIBRARY_NAME})

# GENERAL
if(CI_SERVER STREQUAL "appveyor")
    target_compile_definitions(${PROJECT_NAME} PRIVATE CI_APPVEYOR)
    target_compile_definitions(${UNIT_TEST_NAME} PRIVATE CI_APPVEYOR)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE CI_APPVEYOR)
elseif(CI_SERVER STREQUAL "travis")
    target_compile_definitions(${PROJECT_NAME} PRIVATE CI_TRAVIS)
    target_compile_definitions(${UNIT_TEST_NAME} PRIVATE CI_TRAVIS)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE CI_TRAVIS)
endif()

if(WIN32)
    if(MSVC)
        target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
        target_compile_definitions(${UNIT_TEST_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
        target_compile_definitions(${LIBRARY_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    endif()

    include_directories(C:/Libraries/boost_1_63_0)
    
    # NOTE: these mysql-connector windows thingies only work in release mode.
    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-src/lib/clientlib.lib)
    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-src/lib/mysqlclient.lib)
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-src/lib/clientlib.lib)
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-src/lib/mysqlclient.lib)
    target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-src/lib/clientlib.lib)
    target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-src/lib/mysqlclient.lib)
    
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_DEBUG_MODE)
        target_compile_definitions(${UNIT_TEST_NAME} PRIVATE WIN32_DEBUG_MODE)        
        target_compile_definitions(${LIBRARY_NAME} PRIVATE WIN32_DEBUG_MODE)
        
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/Debug/restbed.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/Debug/restbed.lib)        
        target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/restbed/build/Debug/restbed.lib)

        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/Debug/libcppdb.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/Debug/libcppdb.lib)        
        target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/cppdb/build/Debug/libcppdb.lib)
    else()
        target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_RELEASE_MODE)
        target_compile_definitions(${UNIT_TEST_NAME} PRIVATE WIN32_RELEASE_MODE)        
        target_compile_definitions(${LIBRARY_NAME} PRIVATE WIN32_RELEASE_MODE)
    
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/Release/restbed.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/Release/restbed.lib)        
        target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/restbed/build/Release/restbed.lib)
    
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/Release/libcppdb.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/Release/libcppdb.lib)        
        target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/cppdb/build/Release/libcppdb.lib)
    endif()
else() # not Windows
    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/librestbed.a)
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/librestbed.a)    
    target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/restbed/build/librestbed.a)

    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/libcppdb.a ${CMAKE_DL_LIBS})
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/libcppdb.a ${CMAKE_DL_LIBS})
    target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/cppdb/build/libcppdb.a ${CMAKE_DL_LIBS})

    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/libcppdb_mysql.a ${CMAKE_DL_LIBS})
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/libcppdb_mysql.a ${CMAKE_DL_LIBS})    
    target_link_libraries(${LIBRARY_NAME} ${HOMEDIR}/cppdb/build/libcppdb_mysql.a ${CMAKE_DL_LIBS})
endif()

include_directories(${HOMEDIR}/restbed/source)

include_directories(${HOMEDIR}/rapidjson/include)

include_directories(${HOMEDIR}/GSL/include)

include_directories(${HOMEDIR}/doctest/doctest)

include_directories(${HOMEDIR}/cppdb)
