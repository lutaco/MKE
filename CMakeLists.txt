cmake_minimum_required(VERSION 3.14)
project(mke)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE main.cpp headers.h)

set(SOURCE_LIB CMatrix.cpp)
include_directories(CLinalg CLinalg/CMatrix Solution)
add_subdirectory(CLinalg)
add_subdirectory(Solution)

add_executable(mke ${SOURCE})
target_link_libraries(mke CLinalg)
target_link_libraries(mke Solution)
