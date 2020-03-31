# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e10_2)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Threads library (needed for Linux)
find_package(Threads)

# Source files
set(SRCS
        main.cpp
        )

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
