#=======================================
#                OPTION
#=======================================

option(GLNGINE_USE_STATE_CACHE "Use a cache system for OpenGL state" TRUE)

#=======================================
#                LIBRARY
#=======================================

set(GLNGINE_LIBRARY_NAME OpenGLNgine)
set(GLNGINE_SOURCE OpenGLNgine)

set(GLNGINE_SRC
    ${GLNGINE_SOURCE}/Core/IHardwareManager.cpp
    ${GLNGINE_SOURCE}/Core/IHardwareResource.cpp
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
    ${GLNGINE_SOURCE}/Hardware/Compositor.cpp
    ${GLNGINE_SOURCE}/Hardware/CompositorManager.cpp
    ${GLNGINE_SOURCE}/Hardware/CompositorPass.cpp
    ${GLNGINE_SOURCE}/Hardware/CompositorPassClear.cpp
    ${GLNGINE_SOURCE}/Hardware/CompositorTargetPass.cpp
    ${GLNGINE_SOURCE}/Hardware/HardwareBufferManager.cpp
    ${GLNGINE_SOURCE}/Hardware/HardwareIndexBuffer.cpp
    ${GLNGINE_SOURCE}/Hardware/HardwareVertexBuffer.cpp
    ${GLNGINE_SOURCE}/Hardware/IHardwareBuffer.cpp
    ${GLNGINE_SOURCE}/Hardware/IndexData.cpp
    ${GLNGINE_SOURCE}/Hardware/Material.cpp
    ${GLNGINE_SOURCE}/Hardware/MaterialManager.cpp
    ${GLNGINE_SOURCE}/Hardware/Pass.cpp
    ${GLNGINE_SOURCE}/Hardware/Program.cpp
    ${GLNGINE_SOURCE}/Hardware/ProgramManager.cpp
    ${GLNGINE_SOURCE}/Hardware/RenderTarget.cpp
    ${GLNGINE_SOURCE}/Hardware/RenderTargetManager.cpp
    ${GLNGINE_SOURCE}/Hardware/Shader.cpp
    ${GLNGINE_SOURCE}/Hardware/Texture.cpp
    ${GLNGINE_SOURCE}/Hardware/TextureManager.cpp
    ${GLNGINE_SOURCE}/Hardware/TextureUnitState.cpp
    ${GLNGINE_SOURCE}/Hardware/VertexBufferBinding.cpp
    ${GLNGINE_SOURCE}/Hardware/VertexData.cpp
    ${GLNGINE_SOURCE}/Hardware/VertexDeclaration.cpp
    ${GLNGINE_SOURCE}/Hardware/VertexElement.cpp
    ${GLNGINE_SOURCE}/Render/BoundingBox.cpp
    ${GLNGINE_SOURCE}/Render/Camera.cpp
    ${GLNGINE_SOURCE}/Render/Component.cpp
    ${GLNGINE_SOURCE}/Render/CompositorChain.cpp
    ${GLNGINE_SOURCE}/Render/Light.cpp
    ${GLNGINE_SOURCE}/Render/Mesh.cpp
    ${GLNGINE_SOURCE}/Render/Render.cpp
    ${GLNGINE_SOURCE}/Render/RenderWindow.cpp
    ${GLNGINE_SOURCE}/Render/SceneManager.cpp
    ${GLNGINE_SOURCE}/Render/SceneNode.cpp
    ${GLNGINE_SOURCE}/Render/SceneNode.cpp
    ${GLNGINE_SOURCE}/Render/SubMesh.cpp
    ${GLNGINE_SOURCE}/Render/Viewport.cpp)

set(GLNGINE_HEADER
    ${GLNGINE_SOURCE}/Core/Exception.hpp
    ${GLNGINE_SOURCE}/Core/Helper.hpp
    ${GLNGINE_SOURCE}/Core/IHardwareManager.hpp
    ${GLNGINE_SOURCE}/Core/IHardwareResource.hpp
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
    ${GLNGINE_SOURCE}/Hardware/Compositor.hpp
    ${GLNGINE_SOURCE}/Hardware/CompositorManager.hpp
    ${GLNGINE_SOURCE}/Hardware/CompositorPass.hpp
    ${GLNGINE_SOURCE}/Hardware/CompositorPassClear.hpp
    ${GLNGINE_SOURCE}/Hardware/CompositorTargetPass.hpp
    ${GLNGINE_SOURCE}/Hardware/HardwareBufferManager.hpp
    ${GLNGINE_SOURCE}/Hardware/HardwareIndexBuffer.hpp
    ${GLNGINE_SOURCE}/Hardware/HardwareVertexBuffer.hpp
    ${GLNGINE_SOURCE}/Hardware/IHardwareBuffer.hpp
    ${GLNGINE_SOURCE}/Hardware/IndexData.hpp
    ${GLNGINE_SOURCE}/Hardware/Material.hpp
    ${GLNGINE_SOURCE}/Hardware/MaterialManager.hpp
    ${GLNGINE_SOURCE}/Hardware/Pass.hpp
    ${GLNGINE_SOURCE}/Hardware/Program.hpp
    ${GLNGINE_SOURCE}/Hardware/ProgramManager.hpp
    ${GLNGINE_SOURCE}/Hardware/RenderTarget.hpp
    ${GLNGINE_SOURCE}/Hardware/RenderTargetManager.hpp
    ${GLNGINE_SOURCE}/Hardware/Shader.hpp
    ${GLNGINE_SOURCE}/Hardware/Texture.hpp
    ${GLNGINE_SOURCE}/Hardware/TextureManager.hpp
    ${GLNGINE_SOURCE}/Hardware/TextureUnitState.hpp
    ${GLNGINE_SOURCE}/Hardware/VertexBufferBinding.hpp
    ${GLNGINE_SOURCE}/Hardware/VertexData.hpp
    ${GLNGINE_SOURCE}/Hardware/VertexDeclaration.hpp
    ${GLNGINE_SOURCE}/Hardware/VertexElement.hpp
    ${GLNGINE_SOURCE}/Render/BoundingBox.hpp
    ${GLNGINE_SOURCE}/Render/Camera.hpp
    ${GLNGINE_SOURCE}/Render/Component.hpp
    ${GLNGINE_SOURCE}/Render/CompositorChain.hpp
    ${GLNGINE_SOURCE}/Render/Light.hpp
    ${GLNGINE_SOURCE}/Render/Mesh.hpp
    ${GLNGINE_SOURCE}/Render/Render.hpp
    ${GLNGINE_SOURCE}/Render/RenderWindow.hpp
    ${GLNGINE_SOURCE}/Render/SceneManager.hpp
    ${GLNGINE_SOURCE}/Render/SceneNode.hpp
    ${GLNGINE_SOURCE}/Render/SubMesh.hpp
    ${GLNGINE_SOURCE}/Render/Viewport.hpp)

add_library(${GLNGINE_LIBRARY_NAME} ${GLNGINE_SRC} ${GLNGINE_HEADER})

target_include_directories(${GLNGINE_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#=======================================
#               PROPERTIES
#=======================================

set_target_properties(${GLNGINE_LIBRARY_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )

if(NOT WIN32)
    target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC stdc++fs)
endif(NOT WIN32)

if(${GLNGINE_USE_STATE_CACHE})
    target_compile_definitions(${GLNGINE_LIBRARY_NAME} PUBLIC GLNGINE_USE_STATE_CACHE)
endif(${GLNGINE_USE_STATE_CACHE})

target_compile_options(${GLNGINE_LIBRARY_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
)

#=======================================
#               LIBRARIES
#=======================================

target_link_libraries(${GLNGINE_LIBRARY_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC glfw)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC GLEW::glew)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC GLM::GLM)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PRIVATE SOIL2::SOIL2)
target_link_libraries(${GLNGINE_LIBRARY_NAME} PUBLIC assimp::assimp)

if(${OpenMP_FOUND})
    target_link_libraries(${GLNGINE_LIBRARY_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()
