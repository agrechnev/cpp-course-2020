# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e1_3)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Find Boost library
# Note : This is simple if we use only boost.format which is header-only
# Linking binary libs (.a or .so) is slightly harder
find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

# Source files
set(SRCS 
    main.cpp
)

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})
