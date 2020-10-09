cmake_minimum_required(VERSION 3.10)
project(Assignment3 C)

set(TOOLCHAIN_PREFIX i686-w64-mingw32)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc-posix)
set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX} /usr/lib/gcc/${TOOLCHAIN_PREFIX}/7.3-posix)

set(CMAKE_C_STANDARD 99)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )


add_executable(Problem1.exe src/Problem1.c)
add_executable(Problem2.exe src/Problem2.c)
add_executable(Problem3.exe src/Problem3.c)
add_executable(Problem4.exe src/Problem4.c)

include_directories(src/Problem5)
add_executable(Problem5.exe src/Problem5.c src/Problem5/FilterFunction.c)