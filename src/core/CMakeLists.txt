cmake_minimum_required(VERSION 3.0.0)
project(core VERSION 0.1.0)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)

add_library(core ${SRC})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_LIST_DIR})