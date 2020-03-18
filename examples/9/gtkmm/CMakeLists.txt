cmake_minimum_required(VERSION 3.1)
project(hello)
set(CMAKE_CXX_STANDARD 14)

# gtkmm libraries
find_package(PkgConfig)    # Find pkg-config
pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
   HelloWorld.h
   main.cpp
   )

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES}  )