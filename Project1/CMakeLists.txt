cmake_minimum_required(VERSION 3.7)
project(Project1)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c node.c node.h)
add_executable(Project1 ${SOURCE_FILES})