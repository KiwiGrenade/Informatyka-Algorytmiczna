cmake_minimum_required(VERSION 3.23)
project(AISD_4)

set(CMAKE_CXX_STANDARD 23)

add_executable(zad1 zad1.cpp BinarySearchTree.cpp queue.cpp)
add_executable(RNG RNG.cpp)
add_executable(I_RNG I_RNG.cpp)
add_executable(zad2 zad2.cpp RB_BST.cpp queue.cpp)
add_executable(zad3 zad3.cpp SplayTree.cpp queue.cpp)