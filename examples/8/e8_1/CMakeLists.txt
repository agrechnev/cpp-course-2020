# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e8_1)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Source files
set(SRCS
        Vec2.h
        main.cpp
        )

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})
