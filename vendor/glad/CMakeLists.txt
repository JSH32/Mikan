cmake_minimum_required(VERSION 3.0)
project(glad)

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*.h)
add_library(glad ${SRC})
target_include_directories(glad PUBLIC include/)

set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)