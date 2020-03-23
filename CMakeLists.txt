cmake_minimum_required(VERSION 3.0.0)
project(kos
        VERSION 0.1.0
        LANGUAGES CXX)
project(test
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_library(Console
            Console/Console.hpp)
add_library(FileSys
            FileSys/FileSys.hpp)

set_target_properties(  Console FileSys
                        PROPERTIES LINKER_LANGUAGE CXX)


enable_testing()

add_executable(test_files tests/testFileSys.cpp)
add_test(test test_files)

 

add_executable(kos main.cpp)

target_link_libraries(kos PRIVATE Console PRIVATE FileSys)