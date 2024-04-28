cmake_minimum_required(VERSION 3.27)
project(cpp_2024_1_projektas)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_2024_1_projektas main.cpp
        Backend/FileIO.cpp
        Backend/FileIO.h
        Backend/FileIO.cpp
        Backend/TimeTracker.cpp
        Backend/TimeTracker.h
        Backend/Data.cpp
        Backend/Data.h)
