cmake_minimum_required(VERSION 3.17)
project(Assignment4)
set(CMAKE_CXX_STANDARD 14)

file(GLOB PROJECT_CPP_FILES "src/*.cpp")
file(GLOB PROJECT_HEADER_FILES "inc/*.h")

include_directories(inc/)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(Assignment4 ${PROJECT_CPP_FILES} ${PROJECT_C_FILES} ${PROJECT_HEADER_FILES})