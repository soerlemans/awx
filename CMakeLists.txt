# Set minimum CMake version
cmake_minimum_required(VERSION 3.25.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Set the compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")

# Define the project
project(awx
	VERSION 0.2.0
	DESCRIPTION "An awk interpreter written in C++."
	LANGUAGES CXX
)

# Create version header
configure_file(
	${PROJECT_SOURCE_DIR}/src/version.hpp.in
	${PROJECT_SOURCE_DIR}/src/version.hpp
)

# Define the executable that will be made
add_executable(${PROJECT_NAME})

# Define DEBUG macro if build type is Debug
target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
)

# Set compile flags
# TODO: Compile flags not yet complete
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wextra
  -pedantic
  $<$<CONFIG:Debug>:-ggdb>
  $<$<CONFIG:Debug>:-g3>
  $<$<CONFIG:Release>:-O2>
)

# Clang-tidy setup
set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -checks=*;
  -header-filter=src/.*;
  -extra-arg=c++2b;
)

# Find libraries
find_package(CLI11 CONFIG REQUIRED)

# Link libraries
target_link_libraries(${PROJECT_NAME} CLI11::CLI11)

# Run CMake in src/ subdirectory
add_subdirectory(src)
