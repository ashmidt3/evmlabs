cmake_minimum_required(VERSION 4.1)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -O)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(lab1 lab1.cpp)