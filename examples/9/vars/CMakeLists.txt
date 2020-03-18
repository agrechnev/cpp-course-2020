cmake_minimum_required(VERSION 3.1) # Minimal cmake version required
project(hello)    # Project title
# Language version required: C++ 14. Sets a variable !
set(CMAKE_CXX_STANDARD 14)

# Set options
option(WITH_DRAGONS "Any dragons in our story ?" OFF)
option(WITH_ELVES "Any elves in our story ?" OFF)
option(WITH_ORCS "Any orcs in our story ?" ON)

# Some Variables
message("Variables :")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message("WITH_MAGIC = ${WITH_MAGIC}")
message("WITH_DRAGONS = ${WITH_DRAGONS}")
message("WITH_ELVES = ${WITH_ELVES}")
message("WITH_ORCS = ${WITH_ORCS}")

# Pass definition to C++ using add_definition()
if(DEFINED WITH_DRAGONS)
 add_definitions(-DWITH_DRAGONS=${WITH_DRAGONS})
endif()

# Pass definitions to C++ using configure_file()
configure_file(config.h.in config.h)
include_directories("${PROJECT_BINARY_DIR}")    # To find config.h

# Source files
set(SRCS 
    hello.cpp
)
#  Executable created from ${SRCS}
add_executable(${PROJECT_NAME} ${SRCS})