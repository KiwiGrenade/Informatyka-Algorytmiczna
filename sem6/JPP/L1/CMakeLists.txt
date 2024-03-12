cmake_minimum_required(VERSION 3.27)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

project(L1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include(CTest)

add_executable(C
        src/lib.c
        src/lib.h
        src/test_factorial.cpp)
target_link_libraries(C Catch2::Catch2WithMain)
add_test(TEST1 ./C)