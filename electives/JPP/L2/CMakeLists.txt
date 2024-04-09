cmake_minimum_required(VERSION 3.27)
project(JPP-L2)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_STANDARD 23)

include(CTest)

add_executable(test_GF test_GF.cpp)
add_library(GF GF.cpp)
add_subdirectory(libs)
target_include_directories(GF PUBLIC libs)
target_link_libraries(GF L1_LIB)

target_link_libraries(test_GF PRIVATE
    Catch2::Catch2WithMain
    GF
)

add_test(TEST_GF ./test_GF)