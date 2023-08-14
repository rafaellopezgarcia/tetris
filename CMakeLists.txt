cmake_minimum_required(VERSION 3.10)
project(tetris
        VERSION 1.0.0
        DESCRIPTION "Raw implementation of the classic"
        LANGUAGES CXX)

add_executable(tetris)
target_sources(tetris PRIVATE ./src/main.cpp)
set_property(TARGET tetris PROPERTY CXX_STANDARD 20) 