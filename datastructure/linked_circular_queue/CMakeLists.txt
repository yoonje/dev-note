cmake_minimum_required(VERSION 3.14)
project(datastructure)

set(CMAKE_CXX_STANDARD 14)

add_executable(linked_circular_queue main.cpp LinkedQueue.cpp Node.cpp)