cmake_minimum_required(VERSION 3.23)
project(AISD_4)

set(CMAKE_CXX_STANDARD 23)

add_executable(zad1 zad1.cpp BST.cpp BST.h)
add_executable(RNG RNG.cpp)
add_executable(I_RNG I_RNG.cpp)
add_executable(zad2_cpp zad2.cpp RB_BST.cpp RB_BST.h)
add_executable(zad2_c redblack.cpp RB_BSTree.cpp queue.cpp)
add_executable(splay_tree zad3.cpp SplayTree.cpp queue.cpp)