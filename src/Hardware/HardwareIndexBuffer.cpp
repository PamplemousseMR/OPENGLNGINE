#include "Hardware/HardwareIndexBuffer.hpp"
#include "Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

HardwareIndexBuffer::HardwareIndexBuffer(HardwareBufferManager* const _manager, INDEX_TYPE _type, size_t _numIndex, HARDWAREBUFFER_USAGE _usage):
    IHardwareBuffer(_manager, GL_ELEMENT_ARRAY_BUFFER, _type*_numIndex, _usage),
    m_indexType(_type),
    m_numIndex(_numIndex)
{
}

HardwareIndexBuffer::~HardwareIndexBuffer()
{
    m_manager->_notifyIndexBufferDestroyed(this);
}

}
