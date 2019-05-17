#=======================================
#                PROJECT                
#=======================================

cmake_minimum_required(VERSION 3.8)
project("OPENGLNGINE")

#=======================================
#                 INIT                 
#======================================= 

#---------------------------------------
#               VARIABLES               
#---------------------------------------

set(OPENGLNGINE_SRC_DIR "src")
set(OPENGLNGINE_HEADER_DIR "include")
set(OPENGLNGINE_BIN_DIR "bin")
set(OPENGLNGINE_PROJECT_NAME "openglngine")
set(OPENGLNGINE_GLSL_DIR "${OPENGLNGINE_BIN_DIR}/GLSL")
set(OPENGLNGINE_OBJ_DIR "${OPENGLNGINE_BIN_DIR}/obj")

#---------------------------------------
#                 FILES                 
#---------------------------------------

file(GLOB_RECURSE openglngine_src_files ${OPENGLNGINE_SRC_DIR}/*)
file(GLOB_RECURSE openglngine_header_files ${OPENGLNGINE_HEADER_DIR}/*)
file(GLOB_RECURSE openglngine_glsl_files ${OPENGLNGINE_GLSL_DIR}/*)

#---------------------------------------
#                 CONAN                 
#---------------------------------------

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#=======================================
#                CREATE                
#=======================================

#---------------------------------------
#                PROJECT                
#---------------------------------------

add_executable(${OPENGLNGINE_PROJECT_NAME}  ${openglngine_src_files} ${openglngine_header_files} ${openglngine_glsl_files})
target_include_directories(${OPENGLNGINE_PROJECT_NAME} PRIVATE ${OPENGLNGINE_HEADER_DIR} ${OPENGLNGINE_GLSL_DIR})

#--------------------------------------- 
#              PROPERTIES              
#---------------------------------------

set_target_properties(${OPENGLNGINE_PROJECT_NAME} PROPERTIES
                        CXX_STANDARD 17
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS OFF)

if(NOT WIN32)
    set_target_properties(${OPENGLNGINE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-lstdc++fs -std=c++17")
endif(UNIX)

#---------------------------------------
#                OPENGL                
#---------------------------------------

find_package(OpenGL REQUIRED)

target_link_libraries(${OPENGLNGINE_PROJECT_NAME} OpenGL::GL)

#---------------------------------------
#                 CONAN                 
#---------------------------------------

target_link_libraries(${OPENGLNGINE_PROJECT_NAME} ${CONAN_LIBS})

#---------------------------------------
#               BINARIES               
#---------------------------------------

file(COPY ${OPENGLNGINE_GLSL_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${OPENGLNGINE_OBJ_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
