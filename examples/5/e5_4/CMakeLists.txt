# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e5_4)

# Language version required: C++ 17, need 17 for any, optional !
set(CMAKE_CXX_STANDARD 17)

# Source files
set(SRCS 
    main.cpp
)

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})
