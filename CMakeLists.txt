cmake_minimum_required(VERSION 3.10)

project(GameOfLife)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
	src/main.c
	src/board.c
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GameOfLife ${SOURCES})

target_link_libraries(GameOfLife ${SDL2_LIBRARIES})
