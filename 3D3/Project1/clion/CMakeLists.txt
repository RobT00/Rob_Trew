cmake_minimum_required(VERSION 3.9)
project(clion)

set(CMAKE_CXX_STANDARD 11)

add_executable(clion web-server.cpp async-server.cpp multi-thread.cpp server.cpp showip.cpp HttpRequest.cpp HttpRequest.h HttpResponse.cpp HttpResponse.h)