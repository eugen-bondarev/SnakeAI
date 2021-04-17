cmake_minimum_required(VERSION 3.12)

project(SnakeAI VERSION 0.0.1)

set(target_name SnakeAI)

file(GLOB src
    src/*.cpp
    src/**/*.cpp
    src/**/**/*.cpp
    src/**/**/**/*.cpp
)

add_executable(${target_name} ${src})
target_include_directories(${target_name} PUBLIC src)
target_precompile_headers(${target_name} PUBLIC src/pch.h)

add_subdirectory(external/glew/build/cmake)
add_subdirectory(external/glfw)

target_link_libraries(${target_name} glew_s)
target_link_libraries(${target_name} glfw)

target_include_directories(${target_name} PUBLIC external/glew/include)
target_include_directories(${target_name} PUBLIC external/glfw/include)
target_include_directories(${target_name} PUBLIC src/external)