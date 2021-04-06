cmake_minimum_required(VERSION 3.0.0)
project(app VERSION 0.1.0)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)

add_executable(app ${SRC} ${IMGUI_SRC})
target_include_directories(app PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(app sfml-graphics)

target_link_libraries(app ImGui-SFML::ImGui-SFML)