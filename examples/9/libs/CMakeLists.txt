# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(hello)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Build library a : separate directory liba
add_subdirectory(liba)
# Search for header files (a.h) in liba
include_directories(liba)  

# Build library b : in this directory
# For real projects better use separate directories !
set(SRCS_B
    B.cpp
)
add_library(b SHARED ${SRCS_B})

# Build hello
set(SRCS_HELLO 
    main.cpp
)
add_executable(${PROJECT_NAME} ${SRCS_HELLO})
target_link_libraries(${PROJECT_NAME} a b)