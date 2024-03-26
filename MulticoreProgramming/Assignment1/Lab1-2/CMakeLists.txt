cmake_minimum_required(VERSION 3.9)
project(Lab1-2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)
add_executable(Lab1-2 main.cpp common.h DS_definitions.h DS_timer.cpp DS_timer.h)
target_link_libraries(Lab1-2 PRIVATE OpenMP::OpenMP_CXX)
