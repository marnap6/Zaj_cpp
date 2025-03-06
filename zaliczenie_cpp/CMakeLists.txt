cmake_minimum_required(VERSION 3.27)
project(zadania_ros)

set(CMAKE_CXX_STANDARD 17)

add_executable(zadania_ros main.cpp
        rosalind.cpp
        rosalind.h)
