cmake_minimum_required(VERSION 3.23)
project(SierpinskiGasket)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(SierpinskiGasket main.cpp)
