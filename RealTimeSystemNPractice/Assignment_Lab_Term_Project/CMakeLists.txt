cmake_minimum_required(VERSION 3.11)
project(lab-term)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(mps mps.c)
target_link_libraries (mps -static gcc stdc++ winpthread -dynamic)
add_executable(mps_cv mps_cv.c)
target_link_libraries (mps_cv -static gcc stdc++ winpthread -dynamic)