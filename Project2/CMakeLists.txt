cmake_minimum_required(VERSION 3.7)
project(Project2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c shell.c shell.h floppy.c floppy.h sort.c sort.h)
add_executable(Project2 ${SOURCE_FILES})