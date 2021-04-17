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