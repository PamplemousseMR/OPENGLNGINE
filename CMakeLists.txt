#=======================================
#                PROJECT                
#=======================================

cmake_minimum_required(VERSION 3.8)
project("OPENGLNGINE")

#=======================================
#               LIBRARIES
#=======================================

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3.2 REQUIRED)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glm 0.9.9.8 REQUIRED)
find_package(soil2 1.20 REQUIRED)

#=======================================
#                ENGINE
#=======================================

add_subdirectory("OpenGLNgine")

#=======================================
#                 BIN
#=======================================

add_subdirectory("bin")

#=======================================
#                 APPS
#=======================================

add_subdirectory("app")
