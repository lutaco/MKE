cmake_minimum_required(VERSION 3.14)
project(CLinalg)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_LIB CLinalg.cpp)

include_directories(CMatrix)

add_subdirectory(CMatrix)

add_library(CLinalg STATIC ${SOURCE_LIB})

target_link_libraries(CLinalg CMatrix)