cmake_minimum_required(VERSION 3.1) # Minimal cmake version required
project(lang)    # Project title
# Language version required: C++ 14. Sets a variable !
set(CMAKE_CXX_STANDARD 14)

# Fun with set() and message()
message("Hello world !")
message("PROJECT_NAME = ${PROJECT_NAME}")
message("CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")   # CMAKE_CXX_STANDARD = 14
message(${CMAKE_CXX_STANDARD})  # 14

# math(), result is set to cariable c
message("CMake and arithmetics :")
math(EXPR c "5*(10+13) + 7")
message("5*(10+13) + 7 = ${c}")

# if()
message("if()")
set(n 15)
if(n GREATER 10)
	message("${n} > 10")
else()
	message("${n} < 10")
endif()

#while
message("while()")
set(n 1)
while(n LESS_EQUAL 10)
	message(${n})
	math(EXPR n "${n}+1")
endwhile()

# Some Standard variables
message("Useful CMake variables :")
message("CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_EXECUTABLE_SUFFIX = ${CMAKE_EXECUTABLE_SUFFIX}")
message("CMAKE_SYSTEM = ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SIZEOF_VOID_P = ${CMAKE_SIZEOF_VOID_P}")  # Check for 32/64 bit
message("WIN32 = ${WIN32}")
message("APPLE = ${APPLE}")
message("UNIX = ${UNIX}")
message("MINGW = ${MINGW}")

# Example use in if
if (WIN32)
	message("Windows !!!")
else()
	message("NOT Windows !!!")
endif()
