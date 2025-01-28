cmake_minimum_required(VERSION 3.28)
project(nnpt20)

set(CMAKE_CXX_STANDARD 17)

add_executable(nnpt20 main.cpp
        matrix.h
        tests.h
        layers.h
        model.h
        model.h)
