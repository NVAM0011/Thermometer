cmake_minimum_required(VERSION 4.0)
project(Thermometer)

set(CMAKE_CXX_STANDARD 20)

add_executable(Thermometer
        LCD.cpp
        LCD.h
        main.cpp
)
