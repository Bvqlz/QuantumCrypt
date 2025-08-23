cmake_minimum_required(VERSION 3.30)
project(Quantum)

set(CMAKE_CXX_STANDARD 26)

add_executable(Quantum main.cpp
        src/chunk.h)
