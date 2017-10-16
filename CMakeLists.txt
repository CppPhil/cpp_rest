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
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter")
endif()

if(WIN32)
    set(HOMEDIR $ENV{USERPROFILE})
else()
    set(HOMEDIR $ENV{HOME})
endif()

set(UNIT_TEST_NAME unittest)

set(APPLICATION_HEADER_FILES
    include/rest_service.hpp
    include/namespace_aliases.hpp
    include/http_verb.hpp
    include/rest_api.hpp
    include/example_rest_api.hpp
    include/json.hpp
    include/except.hpp
    include/glue.hpp
    include/stringify.hpp
    include/example_type.hpp
    include/http_status_code.hpp
    include/request.hpp
    include/response.hpp
    include/restbed_logger.hpp
    include/unused.hpp
    include/log.hpp
    include/another_rest_api.hpp
    include/test_type.hpp
    include/database_session.hpp
    include/test_type_repository.hpp
    include/os.hpp
    include/compiler.hpp)

set(APPLICATION_SOURCE_FILES
    src/rest_service.cpp
    src/http_verb.cpp
    src/example_rest_api.cpp
    src/json.cpp
    src/example_type.cpp
    src/http_status_code.cpp
    src/request.cpp
    src/response.cpp
    src/restbed_logger.cpp
    src/log.cpp
    src/another_rest_api.cpp
    src/test_type.cpp
    src/database_session.cpp
    src/test_type_repository.cpp)

set(UNIT_TEST_SOURCE_FILES
    test/src/main.cpp
    test/src/json_test.cpp
    test/src/example_rest_api_test.cpp
    test/src/another_rest_api_test.cpp
    test/src/test_type_repository_test.cpp)

project(cpp_rest)
add_executable(${PROJECT_NAME} "${APPLICATION_HEADER_FILES}" "${APPLICATION_SOURCE_FILES}" "src/main.cpp")

enable_testing()

add_executable(${UNIT_TEST_NAME} "${UNIT_TEST_SOURCE_FILES}" "${APPLICATION_HEADER_FILES}" "${APPLICATION_SOURCE_FILES}")
add_test(Unittest ${UNIT_TEST_NAME})

if(CI_SERVER STREQUAL "appveyor")
    target_compile_definitions(${PROJECT_NAME} PRIVATE CI_APPVEYOR)
    target_compile_definitions(${UNIT_TEST_NAME} PRIVATE CI_APPVEYOR)
elseif(CI_SERVER STREQUAL "travis")
    target_compile_definitions(${PROJECT_NAME} PRIVATE CI_TRAVIS)
    target_compile_definitions(${UNIT_TEST_NAME} PRIVATE CI_TRAVIS)
endif()

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${UNIT_TEST_NAME} Threads::Threads)

if(WIN32)
    if(MSVC)
        target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
        target_compile_definitions(${UNIT_TEST_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    endif()

    include_directories(C:/Libraries/boost_1_63_0)
    
    # NOTE: these mysql-connector windows thingies only work in release mode.
    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-win32/lib/vs14/mysqlclient.lib)
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/mysql-connector-c-6.1.11-win32/lib/vs14/mysqlclient.lib)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_DEBUG_MODE)
        target_compile_definitions(${UNIT_TEST_NAME} PRIVATE WIN32_DEBUG_MODE)
        
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/Debug/restbed.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/Debug/restbed.lib)

        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/Debug/libcppdb.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/Debug/libcppdb.lib)
    else()
        target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_RELEASE_MODE)
        target_compile_definitions(${UNIT_TEST_NAME} PRIVATE WIN32_RELEASE_MODE)
    
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/Release/restbed.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/Release/restbed.lib)
    
        target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/Release/libcppdb.lib)
        target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/Release/libcppdb.lib)
    endif()
else() # not Windows
    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/restbed/build/librestbed.a)
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/restbed/build/librestbed.a)

    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/libcppdb.a ${CMAKE_DL_LIBS})
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/libcppdb.a ${CMAKE_DL_LIBS})

    target_link_libraries(${PROJECT_NAME} ${HOMEDIR}/cppdb/build/libcppdb_mysql.a ${CMAKE_DL_LIBS})
    target_link_libraries(${UNIT_TEST_NAME} ${HOMEDIR}/cppdb/build/libcppdb_mysql.a ${CMAKE_DL_LIBS})
endif()

include_directories(${HOMEDIR}/restbed/source)

include_directories(${HOMEDIR}/rapidjson/include)

include_directories(${HOMEDIR}/GSL/include)

include_directories(${HOMEDIR}/doctest/doctest)

include_directories(${HOMEDIR}/cppdb)
