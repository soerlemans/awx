# Set minimum CMake version
cmake_minimum_required(VERSION 3.25.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Set the compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# C++ debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

# Clang-tidy setup
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=.*;-checks=*;-extra-arg=c++2b")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-extra-arg=c++2b")

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=src/.*;-extra-arg=c++2b")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-header-filter=.*")

# Define the project
project(awx CXX)

# Remove comment for debug information
add_compile_definitions(DEVELOPMENT)

# Define the executable that will be made
add_executable(${PROJECT_NAME})

# Run CMake in subdirectories
add_subdirectory(src)
