#include "OpenGLNgine/Hardware/HardwareVertexBuffer.hpp"

#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

HardwareVertexBuffer::HardwareVertexBuffer(HardwareBufferManager* const _manager, VERTEX_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage):
    IHardwareBuffer(_manager, GL::DT_ARRAY, _type*_numVertices, _usage),
    m_vertexType(_type),
    m_numVertices(_numVertices)
{
}

HardwareVertexBuffer::~HardwareVertexBuffer()
{
    m_manager->_notifyVertexBufferDestroyed(this);
}

}
