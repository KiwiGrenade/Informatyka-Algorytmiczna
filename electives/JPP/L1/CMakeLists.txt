cmake_minimum_required(VERSION 3.26)

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
add_subdirectory(wrappers)
