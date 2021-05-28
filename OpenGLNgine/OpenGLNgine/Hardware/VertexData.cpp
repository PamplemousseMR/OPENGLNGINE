#include "OpenGLNgine/Hardware/VertexData.hpp"

#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

::GL::DRAWCALL_MODE VertexData::getRenderType(VERTEXDATA_RENDERTYPE _type)
{
    switch(_type)
    {
    case VR_POINTS:
        return ::GL::DR_POINTS;
    case VR_LINE_STRIP:
        return ::GL::DR_LINE_STRIP;
    case VR_LINE_LOOP:
        return ::GL::DR_LINE_LOOP;
    case VR_LINES:
        return ::GL::DR_LINES;
    case VR_LINE_STRIP_ADJACENCY:
        return ::GL::DR_LINE_STRIP_ADJACENCY;
    case VR_LINES_ADJACENCY:
        return ::GL::DR_LINES_ADJACENCY;
    case VR_TRIANGLE_STRIP:
        return ::GL::DR_TRIANGLE_STRIP;
    case VR_TRIANGLE_FAN:
        return ::GL::DR_TRIANGLE_FAN;
    case VR_TRIANGLES:
        return ::GL::DR_TRIANGLES;
    case VR_TRIANGLE_STRIP_ADJACENCY:
        return ::GL::DR_TRIANGLE_STRIP_ADJACENCY;
    case VR_TRIANGLES_ADJACENCY:
        return ::GL::DR_TRIANGLES_ADJACENCY;
    default:
        GLNGINE_EXCEPTION("Unhandle render type");
    }
}

VertexData::VertexData(HardwareBufferManager* const _manager) :
    m_manager(_manager)
{
    GLNGINE_ASSERT_IF(!_manager, "The hardware buffer manager mustn't be null");
    m_vertexDeclaration = _manager->createVertexDeclaration();
    m_vertexBufferBinding = _manager->createVertexBufferBinding();
}

VertexData::~VertexData()
{
    m_manager->destroyVertexBufferBinding(m_vertexBufferBinding);
    m_manager->destroyVertexDeclaration(m_vertexDeclaration);
}

}
