cmake_minimum_required(VERSION 3.10)
project(HTTPServer VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
# set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(
    EXECUTABLES 
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/server.cpp
    ${CMAKE_SOURCE_DIR}/src/request.cpp
    ${CMAKE_SOURCE_DIR}/src/response.cpp
    ${CMAKE_SOURCE_DIR}/src/file.cpp
)

include(CTest)

add_subdirectory(external)

if(BUILD_TESTING)
    set(
        TEST_EXECUTABLES
        ${CMAKE_SOURCE_DIR}/test/main.cpp
    )
    add_executable(server_test ${TEST_EXECUTABLES})
    target_link_libraries(server_test PRIVATE GTest::gtest_main)
    target_include_directories(server_test PRIVATE ${PROJECT_INCLUDE_DIR})

    include(GoogleTest)
    gtest_discover_tests(server_test)
endif()

add_executable(server ${EXECUTABLES})
target_include_directories(server PRIVATE ${PROJECT_INCLUDE_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/public DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/config.ini DESTINATION ${CMAKE_BINARY_DIR})
