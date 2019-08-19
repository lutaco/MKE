cmake_minimum_required(VERSION 3.14)
project(CMatrix)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_LIB CMatrix.cpp)

add_library(CMatrix STATIC ${SOURCE_LIB})