cmake_minimum_required(VERSION 3.25)
project(AISD_3)

set(CMAKE_CXX_STANDARD 23)

add_executable(D_RNG D_RNG.cpp)
add_executable(RNG RNG.cpp)
add_executable(I_RNG I_RNG.cpp)
add_executable(BS BinarySearch.cpp)
add_executable(RS RandomSelect.cpp)
add_executable(S DSelect.cpp Select.cpp)
add_executable(QS QS.cpp DSelect.cpp DSelect.h)
add_executable(DP_QS DP_QS.cpp DSelect.cpp DSelect.h)
