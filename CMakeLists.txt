cmake_minimum_required(VERSION 3.17)
project(event-manager-example)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        "library/eventpp/include")

add_executable(event-manager-example main.cpp)