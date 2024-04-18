cmake_minimum_required(VERSION 3.26)
project(JPP-L2)

Include(FetchContent)

#find_package(Java 11 REQUIRED)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 23)

include(CTest)
#include(UseJava)
add_subdirectory(cpp)
add_subdirectory(java)
