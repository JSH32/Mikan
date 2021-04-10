cmake_minimum_required(VERSION 3.0.0)
project(app VERSION 0.1.0)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.h
)

add_executable(app ${SRC})
target_include_directories(app PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS})
set_target_properties(app PROPERTIES OUTPUT_NAME "Mikan") # Change output name

target_link_libraries(app PRIVATE glad)
target_link_libraries(app PRIVATE imgui)
target_link_libraries(app PRIVATE ${SDL2_LIBS})
target_link_libraries(app PRIVATE ${CMAKE_DL_LIBS})

if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET app POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:app>)
    endforeach()
endif()