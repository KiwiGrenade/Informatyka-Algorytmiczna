cmake_minimum_required(VERSION 3.25)
project(AISD_5)

set(CMAKE_CXX_STANDARD 23)

add_executable(ex1 LCSPrint.cpp)
add_executable(ex2 ex2.cpp BinomialHeap.cpp BinomialHeap.h FibonacciHeap.h FibonacciHeap.cpp)
add_executable(RLG RLG.cpp)
add_executable(RNG RNG.cpp)
