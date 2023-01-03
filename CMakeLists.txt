cmake_minimum_required(VERSION 3.24)
project(LFU)

set(CMAKE_CXX_STANDARD 17)

add_executable(LFU main.cpp displayers.h findLeast.h generator.h)
