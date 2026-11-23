cmake_minimum_required(VERSION 3.21)

project(donut LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.26
    GIT_SHALLOW TRUE
)

set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/shader_program.cpp src/io.cpp)

set(GLAD_SOURCE_DIR extern/glad/src)
set(GLAD_INCLUDE_DIR extern/glad/include)
add_library(glad STATIC ${GLAD_SOURCE_DIR}/gl.c)
target_include_directories(glad PUBLIC ${GLAD_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 OpenGL::GL glad)

