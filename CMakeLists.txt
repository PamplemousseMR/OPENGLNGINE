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
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(soil2 REQUIRED)

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
