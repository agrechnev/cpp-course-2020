# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(a)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Source files
set(SRCS 
    a.cpp
)

#  Static library created from ${SRCS}
add_library(${PROJECT_NAME} STATIC ${SRCS})