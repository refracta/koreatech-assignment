cmake_minimum_required(VERSION 3.10)

project(REMSC C)

set(CMAKE_C_STANDARD 99)

add_executable(REMSC main.c remscinterface.c)