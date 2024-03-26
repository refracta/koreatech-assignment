cmake_minimum_required(VERSION 3.9)
project(Lab5-2 LANGUAGES CXX CUDA)

set(ROOT_DIR ${PROJECT_SOURCE_DIR})

file(GLOB PROJECT_SRC ${ROOT_DIR}/*)
set(SOURCES ${PROJECT_SRC})
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

find_package(CUDA)

add_executable(Lab5-2 ${SOURCES})
set_target_properties(Lab5-2 PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_compile_options(Lab5-2 PRIVATE $<$<COMPILE_LANGUAGE:CUDA>: -Xcompiler=-openmp>)
set_property(TARGET Lab5-2 PROPERTY CUDA_ARCHITECTURES 86)

if(APPLE)
    set_property(TARGET Lab5-2 PROPERTY BUILD_RPATH ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
endif()

if(MSVC)
    target_link_options(Lab5-2 PRIVATE "/NODEFAULTLIB:libcmt.lib")
endif()