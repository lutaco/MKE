cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)

# Добавить в сборку статическую библиотеку "MyProgramCore":
add_library(Solution STATIC Solution.cpp)