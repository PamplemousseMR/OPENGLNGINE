CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# http://www.icl.utk.edu/~mgates3/docs/cuda.html
#------------ project ------------
PROJECT("OPENGLNGINE")

#------------ variables ------------
SET(openglngine_src_dir "src")
SET(openglngine_header_dir "include")
SET(openglngine_project_name "openglngine")

#------ find files ------
FILE(GLOB_RECURSE openglngine_src_files ${openglngine_src_dir}/*)
FILE(GLOB_RECURSE openglngine_header_files ${openglngine_header_dir}/*)

#------------ create project ------------
INCLUDE_DIRECTORIES(${openglngine_header_dir})
ADD_EXECUTABLE(${openglngine_project_name}  ${openglngine_src_files} ${openglngine_header_files})


#------ find opengl ------
FIND_PACKAGE("OPENGL")

IF(NOT ${OPENGL_FOUND})
    MESSAGE(FATAL_ERROR "Can't find OpenGL")
ENDIF()

TARGET_LINK_LIBRARIES(${openglngine_project_name} ${OPENGL_LIBRARY})
