# Minimal cmake version required
cmake_minimum_required(VERSION 3.1)

# Project title
project(e7_6)

# Language version required: C++ 14
set(CMAKE_CXX_STANDARD 14)

# Check that we have pkgconfig
find_package(PkgConfig)
# Find gtkmm-3.0 with pkgconfig
pkg_check_modules(GTKMM gtkmm-3.0)
                                  
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 

message("GTKMM_INCLUDE_DIRS = ${GTKMM_INCLUDE_DIRS}")
message("GTKMM_LIBRARY_DIRS = ${GTKMM_LIBRARY_DIRS}")
message("GTKMM_LIBRARIES = ${GTKMM_LIBRARIES}")

# Usually not needed, but it's good style with pkgconfig
link_directories(${GTKMM_LIBRARY_DIRS}  )
# Add gtkmm to include search path
include_directories(${GTKMM_INCLUDE_DIRS}  )


# Source files
set(SRCS
        HelloWorld.h
        main.cpp
        )

#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
