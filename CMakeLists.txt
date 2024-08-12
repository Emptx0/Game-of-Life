cmake_minimum_required(VERSION 3.26)
project(Game_of_life)

set(CMAKE_CXX_STANDARD 17)

add_executable(Game_of_life main.cpp
        Field.cpp
        Field.h
        Menu.cpp
        Menu.h
)
