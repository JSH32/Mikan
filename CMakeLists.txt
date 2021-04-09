cmake_minimum_required(VERSION 3.0.0)
project(Mikan VERSION 0.1.0)

# GLFW
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glfw)

# GLAD
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glad)

# IMGUI
file(GLOB IMGUI_SRC ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/*.cpp ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui_impl/*.cpp)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui_impl)
target_link_libraries(imgui PRIVATE glad)
target_link_libraries(imgui PRIVATE glfw)

# Projects
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/app)