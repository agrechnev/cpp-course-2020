# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e5_6)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Eigen
find_package(Eigen3 REQUIRED)
message("EIGEN3_INCLUDE_DIR = ${EIGEN3_INCLUDE_DIR}")
include_directories(${EIGEN3_INCLUDE_DIR})

# Source files
set(SRCS 
    main.cpp
)

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})
