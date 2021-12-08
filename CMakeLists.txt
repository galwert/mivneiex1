cmake_minimum_required(VERSION 3.16)
project(AVL)

set(CMAKE_CXX_STANDARD 14)

add_executable(AVL main.cpp player.h group.h player.cpp group.cpp SquidGame.h SquidGame.cpp
       library.h library.cpp main.cpp BinarySearchTree.cpp BinarySearchTree.h)
