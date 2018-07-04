CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#------------ project ------------
PROJECT("OPENGLNGINE")

#------ execute conan ------
SET(openglngine_conan_cmd "conan")
SET(openglngine_conan_arg1 "install")
SET(openglngine_conan_arg2 "-s")
SET(openglngine_conan_arg3 "build_type=${CMAKE_BUILD_TYPE}")
SET(openglngine_conan_arg4 "-if")
SET(openglngine_conan_arg5 ${CMAKE_BINARY_DIR})
SET(openglngine_conan_arg6 ${PROJECT_SOURCE_DIR})

EXECUTE_PROCESS(COMMAND ${openglngine_conan_cmd} ${openglngine_conan_arg1} ${openglngine_conan_arg2} ${openglngine_conan_arg3} ${openglngine_conan_arg4} ${openglngine_conan_arg5} ${openglngine_conan_arg6} RESULT_VARIABLE openglngine_error)

IF(NOT ${openglngine_error} STREQUAL "0")
    MESSAGE(FATAL_ERROR "Can't execute conan : " ${openglngine_conan_cmd} " " ${openglngine_conan_arg1} " " ${openglngine_conan_arg2} " " ${openglngine_conan_arg3} " " ${openglngine_conan_arg4} " " ${openglngine_conan_arg5} " " ${openglngine_conan_arg6})
ENDIF()

    #------------ todo ------------
    LINK_DIRECTORIES("C:/Users/romain/Desktop/OPENGLNGINE/libs/lib/release")

#------------ variables ------------
SET(openglngine_src_dir "src")
SET(openglngine_header_dir "include")
SET(openglngine_project_name "openglngine")

#------------ find files ------------
FILE(GLOB_RECURSE openglngine_src_files ${openglngine_src_dir}/*)
FILE(GLOB_RECURSE openglngine_header_files ${openglngine_header_dir}/*)

#------------ get conan libraries ------------
INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

#------------ create project ------------
INCLUDE_DIRECTORIES(${openglngine_header_dir})
ADD_EXECUTABLE(${openglngine_project_name}  ${openglngine_src_files} ${openglngine_header_files})

#------------ find opengl ------------
FIND_PACKAGE("OPENGL")

IF(NOT ${OPENGL_FOUND})
    MESSAGE(FATAL_ERROR "Can't find OpenGL")
ENDIF()

TARGET_INCLUDE_DIRECTORIES(${openglngine_project_name} PRIVATE ${OPENGL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${openglngine_project_name} ${OPENGL_LIBRARY})

#------ link with libraries created by conan ------
TARGET_LINK_LIBRARIES(${openglngine_project_name} ${CONAN_LIBS})

    #------ todo ------
    INCLUDE_DIRECTORIES("libs/include")
    TARGET_LINK_LIBRARIES(${openglngine_project_name} "SOIL")
