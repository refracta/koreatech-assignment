cmake_minimum_required(VERSION 3.26)
project(lab5)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(sjf sjf.cpp)
add_executable(srtf srtf.cpp)
add_executable(fcfs fcfs.cpp)
