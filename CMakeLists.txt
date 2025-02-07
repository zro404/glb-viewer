cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(DEBUG_COMPILE_OPTIONS "$<$<CONFIG:Debug>:-g;-Wall;-Wextra;-Werror>")
set(RELEASE_COMPILE_OPTIONS "$<$<CONFIG:Release>:-O3>")
set(COMPILE_OPTIONS ${DEBUG_COMPILE_OPTIONS} ${RELEASE_COMPILE_OPTIONS})

project(glb-viewer)

add_executable(${PROJECT_NAME})

set(SOURCES src/main.c src/glad.h src/glad.c src/shaders.c)

add_subdirectory(deps/glfw)
find_package(OpenGL REQUIRED)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw)
