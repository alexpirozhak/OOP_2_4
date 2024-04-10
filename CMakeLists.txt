cmake_minimum_required(VERSION 3.27)
project(OOP_lab_2_4)

set(CMAKE_CXX_STANDARD 23)

add_executable(OOP_lab_2_4 main.cpp
        Matrix.cpp)

add_subdirectory(Google_tests)
