cmake_minimum_required(VERSION 3.26)
project(OPEN_MP_SCHEDULE C)

set(CMAKE_C_FLAGS "-fopenmp")
set(CMAKE_C_STANDARD 11)

add_executable(OPEN_MP_SCHEDULE main.c
        task.c
        task.h)
