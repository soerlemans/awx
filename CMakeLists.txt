# TODO: Make this work
cmake_minimum_required(VERSION 3.25.1)

project(Awx CXX)

set(CMAKE_CXX_STANDARD 20)

# set(AWX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# set(AWX_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)

# add_executable(awx)
