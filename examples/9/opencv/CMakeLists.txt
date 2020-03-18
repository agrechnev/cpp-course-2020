cmake_minimum_required(VERSION 3.0)
project( grabcam )
set (CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( grabcam grabcam.cpp )
target_link_libraries( grabcam ${OpenCV_LIBS} )
