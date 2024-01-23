cmake_minimum_required(VERSION 3.15)
project(homework04)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp)

add_executable(homework04 ${SOURCES})

add_subdirectory(strategies)
add_subdirectory(game)

target_link_libraries(homework04 strategies game)
