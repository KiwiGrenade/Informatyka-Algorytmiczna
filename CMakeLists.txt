cmake_minimum_required(VERSION 3.23)
project(AISD2)

set(CMAKE_CXX_STANDARD 23)

add_executable(RNG RNG.cpp)
add_executable(D_RNG D_RNG.cpp)
add_executable(I_RNG I_RNG.cpp)
add_executable(IS IS.cpp)
add_executable(MS MS.cpp)
add_executable(QS QS.cpp)
add_executable(DP_QS DP_QS.cpp)
add_executable(HYB)