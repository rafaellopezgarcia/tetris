cmake_minimum_required(VERSION 3.10)
project(tetris
        VERSION 1.0.0
        DESCRIPTION "Raw implementation of the classic"
        LANGUAGES CXX)

find_package(Curses REQUIRED)

add_executable(tetris)
target_sources(tetris PRIVATE ./src/main.cpp)
target_include_directories(tetris PRIVATE ./src 
                                           ${CURSES_INCLUDE_DIR})
target_link_libraries (tetris ${CURSES_LIBRARIES})
set_property(TARGET tetris PROPERTY CXX_STANDARD 20) 