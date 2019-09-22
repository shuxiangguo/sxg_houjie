cmake_minimum_required(VERSION 3.14)
project(STL)

set(CMAKE_CXX_STANDARD 14)

add_executable(iterator_category iterator_category.cpp)
add_executable(accumulate accumulate.cpp)
add_executable(stl_test stl_test.cpp)