# ---------------------------------------------
# Header for CMake
# ---------------------------------------------
cmake_minimum_required(VERSION 3.10)
project(echo_program)
set(CMAKE_CXX_STANDARD 20)


# ---------------------------------------------
# Guideline Support Library
# sudo apt update
# sudo apt install libmsgsl-dev
# ---------------------------------------------


# ---------------------------------------------
# Executable for CMake
# ---------------------------------------------
add_executable(echo_program echo_program.cpp)

# ---------------------------------------------
# Commands for CMake
# mkdir build && cd build
# cmake -G "Unix Makefiles" ..
# make -j 8
# ./echo_program
# ---------------------------------------------
