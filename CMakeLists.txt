CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#------------ project ------------
PROJECT("OPENGLNGINE")

#------------ variables ------------
SET(openglngine_src_dir "src")
SET(openglngine_header_dir "include")
SET(openglngine_bin_dir "bin")
SET(openglngine_project_name "openglngine")
SET(openglngine_glsl_dir "${openglngine_bin_dir}/GLSL")
SET(openglngine_obj_dir "${openglngine_bin_dir}/obj")

#------------ cmake variables ------------
SET(CMAKE_CXX_STANDARD 17)

#------------ find files ------------
FILE(GLOB_RECURSE openglngine_src_files ${openglngine_src_dir}/*)
FILE(GLOB_RECURSE openglngine_header_files ${openglngine_header_dir}/*)
FILE(GLOB_RECURSE openglngine_glsl_files ${openglngine_glsl_dir}/*)

#------------ get conan libraries ------------
INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

#------------ create project ------------
ADD_EXECUTABLE(${openglngine_project_name}  ${openglngine_src_files} ${openglngine_header_files} ${openglngine_glsl_files})
TARGET_INCLUDE_DIRECTORIES(${openglngine_project_name} PRIVATE ${openglngine_header_dir} ${openglngine_glsl_dir})

#------------ find opengl ------------
FIND_PACKAGE("OpenGL")

IF(NOT ${OPENGL_FOUND})
    MESSAGE(FATAL_ERROR "Can't find OpenGL")
ENDIF()

TARGET_INCLUDE_DIRECTORIES(${openglngine_project_name} PRIVATE ${OPENGL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${openglngine_project_name} ${OPENGL_LIBRARY})

#------ link with libraries created by conan ------
TARGET_LINK_LIBRARIES(${openglngine_project_name} ${CONAN_LIBS})

#------ copy binary files ------
FILE(COPY ${openglngine_glsl_dir} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
FILE(COPY ${openglngine_obj_dir} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
