cmake_minimum_required(VERSION 3.17)
project(Chap01-Triangle)

# added the line below to find libraries for threading
find_package(Threads)

set(CMAKE_CXX_STANDARD 20)
set(ROOT_DIR "${PROJECT_SOURCE_DIR}")
set(SRC "${ROOT_DIR}/src")
set(LIB "${ROOT_DIR}/contrib/lib")

# added the line below to enable c++11 features
set(INCLUDE "${ROOT_DIR}/contrib/includes")

link_directories("${LIB}")
include_directories("${INCLUDE}")

message("INCLUDE PATH: ${INCLUDE}")

file(GLOB PROJECT_SRC "${ROOT_DIR}/src/*")

set(SOURCES "${PROJECT_SRC}" "${INCLUDE}/gtest/gtest.h")

add_executable(Chap01-Triangle "${SOURCES}")

# modified the line below to express link dependency on gtest and thread libraries
# lib prefix can be omitted here
target_link_libraries(Chap01-Triangle gtest ${CMAKE_THREAD_LIBS_INIT})