# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e6_8)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Copy the file to build directory at the "cmake .." stage
file(COPY hero.json DESTINATION .)

# RapidJSON
find_package(RapidJSON REQUIRED)
message("RAPIDJSON_INCLUDE_DIRS = ${RAPIDJSON_INCLUDE_DIRS}")
include_directories(${RAPIDJSON_INCLUDE_DIRS})

# Source files
set(SRCS
        main.cpp
        )

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})
