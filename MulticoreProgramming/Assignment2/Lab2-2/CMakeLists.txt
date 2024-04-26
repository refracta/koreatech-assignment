cmake_minimum_required(VERSION 3.9)
project(Lab2-2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(ROOT_DIR "${PROJECT_SOURCE_DIR}")
file(GLOB PROJECT_SRC "${ROOT_DIR}/*")
set(SOURCES "${PROJECT_SRC}")

find_package(OpenMP REQUIRED)

add_executable(Lab2-2 "${SOURCES}")
target_link_libraries(Lab2-2 PRIVATE OpenMP::OpenMP_CXX)
