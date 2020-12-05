cmake_minimum_required(VERSION 3.14)
project(datastructure)

set(CMAKE_CXX_STANDARD 14)

add_executable(double_linked_list main.cpp DLinkedList.cpp Node.cpp)