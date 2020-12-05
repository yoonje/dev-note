cmake_minimum_required(VERSION 3.14)
project(datastructure)

set(CMAKE_CXX_STANDARD 14)

add_executable(chaining_hash_map main.cpp Record.cpp HashChainMap.cpp)