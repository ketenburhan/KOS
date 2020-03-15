cmake_minimum_required(VERSION 3.0.0)
project(kos VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library(Console
            Console/Console.h
            Console/Console.cpp)

add_executable(kos main.cpp)

target_link_libraries(kos PRIVATE Console)