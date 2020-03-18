cmake_minimum_required (VERSION 3.0) 
set(CMAKE_CXX_STANDARD 14)
project (triangle)

# Find OpenGL, GLEW, GLFW :
find_library(GLFW_LIB NAMES glfw glfw3)
find_library(GLEW_LIB NAMES glew GLEW glew32)
find_package(OpenGL REQUIRED)
#message("OPENGL_gl_LIBRARY = ${OPENGL_gl_LIBRARY}")
#message("OPENGLu_gl_LIBRARY = ${OPENGL_glu_LIBRARY}")
set(GL_LIBS ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_gl_LIBRARY})

# Build executables
add_executable(triangle triangle.cpp)
target_link_libraries(triangle ${GL_LIBS})
