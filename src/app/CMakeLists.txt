cmake_minimum_required(VERSION 3.0.0)
project(app VERSION 0.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt
find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE SRC 
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.h
    ${CMAKE_CURRENT_LIST_DIR}/resources.qrc
)

add_executable(app ${SRC})
target_include_directories(app PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(app PUBLIC ${Qt5Widgets_INCLUDE_DIRS})

qt5_use_modules(app Widgets)