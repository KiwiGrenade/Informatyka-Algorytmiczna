cmake_minimum_required(VERSION 3.27)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

project(L1)

set(CMAKE_C_STANDARD 99)

include(CTest)

add_subdirectory(libs)

add_executable(C
        test_1.cpp)

target_link_libraries(C Catch2::Catch2WithMain)
target_link_libraries(C MathFunctions)

target_include_directories(C PUBLIC libs)

add_test(TEST1 ./C)