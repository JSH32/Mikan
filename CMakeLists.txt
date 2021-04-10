cmake_minimum_required(VERSION 3.0.0)
project(Mikan VERSION 0.1.0)

# Set policies
cmake_policy(SET CMP0074 NEW)

# Add custom cmake scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# Download file
function(download_file url filename)
    if(NOT EXISTS ${filename})
        file(DOWNLOAD ${url} ${filename}
            TIMEOUT 60  # seconds
            TLS_VERIFY ON)
    endif()
endfunction(download_file)

# Download SDL for windows
if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    set(SDL_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14)
    set(SDL_ZIP ${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14.zip)
    if(NOT EXISTS ${SDL_DIR})
        download_file("https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip" ${SDL_ZIP})
        file(ARCHIVE_EXTRACT INPUT ${SDL_ZIP} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/vendor)
        file(REMOVE ${SDL_ZIP})
    endif()
endif()

# Get SDL library
set(SDL2_ROOT ${CMAKE_CURRENT_LIST_DIR}/vendor/SDL2-2.0.14)
find_package(SDL2 REQUIRED COMPONENTS main)

# GLAD
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/glad)

# IMGUI
file(GLOB_RECURSE IMGUI_SRC ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui/*.cpp)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/vendor/imgui ${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS})
target_link_libraries(imgui PUBLIC ${SDL2_LIBS})
target_link_libraries(imgui PUBLIC glad)

# Projects
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/app)