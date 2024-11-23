cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(HTTPServer)

add_executable(server.out src/main.cpp)
add_executable(client.out src/client.cpp)