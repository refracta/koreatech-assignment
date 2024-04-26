cmake_minimum_required(VERSION 3.9)
project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(ROOT_DIR "${PROJECT_SOURCE_DIR}")
file(GLOB PROJECT_SRC "${ROOT_DIR}/*")
set(SOURCES "${PROJECT_SRC}")

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(OpenMP REQUIRED)

add_executable(Lab3 "${SOURCES}")
target_link_libraries(Lab3 PRIVATE OpenMP::OpenMP_CXX)
