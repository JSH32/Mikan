cmake_minimum_required(VERSION 3.0.0)
project(app VERSION 0.1.0)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)

add_executable(app ${SRC})
target_include_directories(app PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# GLAD and GLFW
target_link_libraries(app PRIVATE glad)
target_link_libraries(app PRIVATE glfw)
target_link_libraries(app PRIVATE imgui)