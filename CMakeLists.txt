cmake_minimum_required(VERSION 3.16)
project(Hikari)

set(CMAKE_CXX_STANDARD 17)

# Agregamos raylib como subproyecto
add_subdirectory(third_party/raylib)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(Hikari ${SRC_FILES})

target_link_libraries(Hikari raylib)