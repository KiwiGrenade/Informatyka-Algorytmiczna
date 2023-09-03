cmake_minimum_required(VERSION 3.24)
project(Zad1_2 C)

set(CMAKE_C_STANDARD 23)

add_executable(Zad1_2 main.c FIFO.c OneWayList.h LIFO.c LIFO.h FIFO.h OneWayList.c)
