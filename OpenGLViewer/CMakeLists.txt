#=======================================
#                EXECUTABLE
#=======================================

set(GLNGINE_APP_NAME OpenGLViewer)

set(GLNGINE_SRC
        main.cpp)

set(GLNGINE_HEADER)

set(GLNGINE_GLSL
        GLSL/OpenGLViewer_FP.glsl
        GLSL/OpenGLViewer_VP.glsl)

add_executable(${GLNGINE_APP_NAME} ${GLNGINE_SRC} ${GLNGINE_HEADER} ${GLNGINE_GLSL})

target_link_libraries(${GLNGINE_APP_NAME} PRIVATE OpenGLNgine)

set_target_properties(${GLNGINE_APP_NAME} PROPERTIES
                        CXX_STANDARD 17
                        CXX_STANDARD_REQUIRED ON
                        CXX_EXTENSIONS OFF)

target_compile_definitions(${GLNGINE_APP_NAME} PRIVATE GLNGINE_GLSL_PATH="${CMAKE_SOURCE_DIR}/OpenGLViewer/GLSL")
target_compile_definitions(${GLNGINE_APP_NAME} PRIVATE MODEL_PATH="${CMAKE_SOURCE_DIR}/sample/bin/Model")
