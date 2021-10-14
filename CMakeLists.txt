#=======================================
#                PROJECT                
#=======================================

cmake_minimum_required(VERSION 3.8)
project("OPENGLNGINE")

#=======================================
#                 CONAN                 
#=======================================

option(OPENGLNGINE_CONAN_BUILD_DEPENDENCIES "automatically build dependencies with conan" FALSE)
if(OPENGLNGINE_CONAN_BUILD_DEPENDENCIES)

    set(OPENGLNGINE_CONAN_USER_AND_CHANNEL "" CACHE STRING "user/channel")

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
      message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
      file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                    "${CMAKE_BINARY_DIR}/conan.cmake"
                    EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                    TLS_VERIFY ON)
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_configure(REQUIRES 
                            "glm/0.9.9.8@${OPENGLNGINE_CONAN_USER_AND_CHANNEL}"
                            "glew/2.2.0@${OPENGLNGINE_CONAN_USER_AND_CHANNEL}"
                            "glfw/3.3.4@${OPENGLNGINE_CONAN_USER_AND_CHANNEL}"
                            "soil2/1.20@${OPENGLNGINE_CONAN_USER_AND_CHANNEL}"
                            "assimp/5.0.1@${OPENGLNGINE_CONAN_USER_AND_CHANNEL}"
                          OPTIONS 
                            "*:shared=True"
                          GENERATORS 
                            "cmake"
                            "cmake_find_package"
                          IMPORTS 
                            "bin, *.dll -> ./bin"
                            "lib, *.dylib* -> ./bin")

    conan_cmake_autodetect(settings)

    conan_cmake_install(PATH_OR_REFERENCE .
                        SETTINGS ${settings}
                        INSTALL_FOLDER ${CMAKE_BINARY_DIR})

    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

#=======================================
#               LIBRARIES
#=======================================

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED CONFIG)
find_package(glfw3 REQUIRED CONFIG)
find_package(SOIL2 REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenMP)

#=======================================
#                ENGINE
#=======================================

add_subdirectory("OpenGLNgine")

#=======================================
#              OpenGLViewer
#=======================================

add_subdirectory("OpenGLViewer")

#=======================================
#                 SAMPLE                
#=======================================

add_subdirectory("sample")
