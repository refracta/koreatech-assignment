cmake_minimum_required(VERSION 3.23)
project(Assignment7)

set(CMAKE_CXX_STANDARD 20)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(Assignment7 main.cpp SplitView.hpp Mesh.hpp glk.h glk.cpp glkWin.cpp Robot.hpp Animation.hpp RunAnimation.hpp EmptyAnimation.hpp MathUtils.h FlyKickAnimation.hpp)
