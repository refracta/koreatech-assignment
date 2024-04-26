cmake_minimum_required(VERSION 3.9)
project(Lab1-1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)
add_executable(Lab1-1 main.cpp)
target_link_libraries(Lab1-1 PRIVATE OpenMP::OpenMP_CXX)
