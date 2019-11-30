#include "Hardware/HardwareVertexBuffer.hpp"
#include "Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

HardwareVertexBuffer::HardwareVertexBuffer(HardwareBufferManager* const _manager, size_t _vertexSizeInBytes, size_t _numVertices, USAGE _usage):
    IHardwareBuffer(_manager, GL_ARRAY_BUFFER, _vertexSizeInBytes*_numVertices, _usage),
    m_vertexSizeInBytes(_vertexSizeInBytes),
    m_numVertices(_numVertices)
{
}

HardwareVertexBuffer::~HardwareVertexBuffer()
{
    m_manager->_notifyVertexBufferDestroyed(this);
}

}
