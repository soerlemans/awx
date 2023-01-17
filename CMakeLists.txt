# TODO: Make this work
cmake_minimum_required(VERSION 3.10)

project(awx CXX)

set(AWX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(AWX_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_executable(awx)
