cmake_minimum_required(VERSION 3.0.0)
project(Mikan VERSION 0.1.0)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/app)

set(IMGUI_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui)
set(IMGUI_SFML_FIND_SFML FALSE)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/imgui-sfml)