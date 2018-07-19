cmake_minimum_required(VERSION 3.10)
project(strongly_connected_components)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(strongly_connected_components
        README.md
        SCC.cpp
        SCC.hpp
        test.cpp test_tarjan_nuutila.cpp)
