cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)

project(AutoGrader)

add_executable(TestGen Generator.cpp ../lib/json.hpp)