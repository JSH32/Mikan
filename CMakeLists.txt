cmake_minimum_required(VERSION 3.0.0)
project(Mikan VERSION 0.1.0)

# Resource packer
include(${CMAKE_CURRENT_LIST_DIR}/vendor/cmake/cmrc/CMakeRC.cmake)

# GLFW
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glfw)

# GLAD
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glad)

# IMGUI
file(GLOB_RECURSE IMGUI_SRC ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/*.cpp)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui ${SDL2_INCLUDE_DIR})
target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(imgui PUBLIC glad)

# stb
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_LIST_DIR}/vendor/stb)

# Projects
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/app)