cmake_minimum_required(VERSION 3.7)
project(Project3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c shell.c shell.h)
add_executable(Project3 ${SOURCE_FILES})