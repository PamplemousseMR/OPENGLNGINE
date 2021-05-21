#=======================================
#                LIBRARY
#=======================================

set(GLNGINE_LIBRARY_NAME OpenGLNgine)
set(GLNGINE_SOURCE OpenGLNgine)

set(GLNGINE_SRC
    ${GLNGINE_SOURCE}/Core/IResource.cpp
    ${GLNGINE_SOURCE}/GL/DataBuffer.cpp
    ${GLNGINE_SOURCE}/GL/DrawCall.cpp
    ${GLNGINE_SOURCE}/GL/FrameBuffer.cpp
    ${GLNGINE_SOURCE}/GL/IBindable.cpp
    ${GLNGINE_SOURCE}/GL/PixelOperation.cpp
    ${GLNGINE_SOURCE}/GL/Program.cpp
    ${GLNGINE_SOURCE}/GL/Rasterizer.cpp
    ${GLNGINE_SOURCE}/GL/RenderBuffer.cpp
    ${GLNGINE_SOURCE}/GL/Shader.cpp
    ${GLNGINE_SOURCE}/GL/Texture.cpp
    ${GLNGINE_SOURCE}/GL/Uniform.cpp
    ${GLNGINE_SOURCE}/GL/VertexArrayBuffer.cpp
    ${GLNGINE_SOURCE}/Render/Camera.cpp
    ${GLNGINE_SOURCE}/Render/Render.cpp
    ${GLNGINE_SOURCE}/Render/RenderWindow.cpp
    ${GLNGINE_SOURCE}/Render/Viewport.cpp)

set(GLNGINE_HEADER
    ${GLNGINE_SOURCE}/Core/Exception.hpp
    ${GLNGINE_SOURCE}/Core/IResource.hpp
    ${GLNGINE_SOURCE}/GL/DrawCall.hpp
    ${GLNGINE_SOURCE}/GL/DataBuffer.hpp
    ${GLNGINE_SOURCE}/GL/FrameBuffer.hpp
    ${GLNGINE_SOURCE}/GL/IBindable.hpp
    ${GLNGINE_SOURCE}/GL/PixelOperation.hpp
    ${GLNGINE_SOURCE}/GL/Program.hpp
    ${GLNGINE_SOURCE}/GL/Rasterizer.hpp
    ${GLNGINE_SOURCE}/GL/RenderBuffer.hpp
    ${GLNGINE_SOURCE}/GL/Shader.hpp
    ${GLNGINE_SOURCE}/GL/Texture.hpp
    ${GLNGINE_SOURCE}/GL/Uniform.hpp
    ${GLNGINE_SOURCE}/GL/VertexArrayBuffer.hpp
    ${GLNGINE_SOURCE}/Render/Camera.hpp
    ${GLNGINE_SOURCE}/Render/Render.hpp
    ${GLNGINE_SOURCE}/Render/RenderWindow.hpp
    ${GLNGINE_SOURCE}/Render/Viewport.hpp)

add_library(${GLNGINE_LIBRARY_NAME} ${GLNGINE_SRC} ${GLNGINE_HEADER})

target_include_directories(${GLNGINE_LIBRARY_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

#=======================================
#               PROPERTIES
#=======================================

set_target_properties(${GLNGINE_LIBRARY_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )

if(NOT WIN32)
    set_target_properties(${GLNGINE_LIBRARY_NAME} PROPERTIES COMPILE_FLAGS "-lstdc++fs")
endif(NOT WIN32)

#=======================================
#               LIBRARIES
#=======================================

target_link_libraries(${GLNGINE_LIBRARY_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC glfw::glfw)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC GLEW::GLEW)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC glm::glm)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PRIVATE soil2::soil2)
