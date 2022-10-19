cmake_minimum_required(VERSION 2.5 FATAL_ERROR)

project(fenton LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
