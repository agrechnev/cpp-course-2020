# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e3_4)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Source files
set(SRCS
    myfile.h myfile.cpp
    main.cpp
)

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})