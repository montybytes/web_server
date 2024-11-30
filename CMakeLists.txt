cmake_minimum_required(VERSION 3.10)
project(HTTPServer VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(
    EXECUTABLES 
    ${CMAKE_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_SOURCE_DIR}/src/request.cpp
)

add_executable(server.out ${EXECUTABLES})
target_include_directories(server.out PRIVATE ${PROJECT_INCLUDE_DIR})