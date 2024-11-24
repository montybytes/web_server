cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(HTTPServer VERSION 0.1)

add_executable(server.out src/main.cpp)