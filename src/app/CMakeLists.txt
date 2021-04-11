cmake_minimum_required(VERSION 3.0.0)
project(app VERSION 0.1.0)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)

add_executable(app ${SRC})
target_include_directories(app PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR}/generated)
set_target_properties(app PROPERTIES OUTPUT_NAME "Mikan") # Change output name

target_link_libraries(app PRIVATE glad)
target_link_libraries(app PRIVATE glfw)
target_link_libraries(app PRIVATE imgui)
target_link_libraries(app PRIVATE stb)

# Resources
set(RESOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/resources)
file(GLOB_RECURSE RESOURCES ${RESOURCE_DIR}/*)
cmrc_add_resource_library(resources NAMESPACE resources WHENCE ${RESOURCE_DIR} ${RESOURCES})
target_link_libraries(app PUBLIC resources)

# SET VARIABLES
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND git rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND git show -s --format=%cd --date=local
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_DATE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Set variables
add_definitions("-DGIT_COMMIT_HASH=${GIT_COMMIT_HASH}")
add_definitions("-DGIT_BRANCH=${GIT_BRANCH}")
add_definitions("-DGIT_COMMIT_DATE=${GIT_COMMIT_DATE}")
configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h)