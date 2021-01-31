#include "OpenGLNgine/Hardware/HardwareIndexBuffer.hpp"

#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

GL::DATABUFFER_TYPE HardwareIndexBuffer::getType(INDEX_TYPE _type)
{
    switch(_type)
    {
    case IT_UNSIGNED_BYTE:
        return GL::DT_UNSIGNED_BYTE;
    case IT_UNSIGNED_SHORT:
        return GL::DT_UNSIGNED_SHORT;
    case IT_UNSIGNED_INT:
        return GL::DT_UNSIGNED_INT;
    default:
        GLNGINE_EXCEPTION("Unhandle index type");
    }
}

HardwareIndexBuffer::HardwareIndexBuffer(HardwareBufferManager* const _manager, INDEX_TYPE _type, size_t _numIndex, HARDWAREBUFFER_USAGE _usage):
    IHardwareBuffer(_manager, GL::ET_ELEMENT, _type*_numIndex, _usage),
    m_indexType(_type),
    m_numIndex(_numIndex)
{
}

HardwareIndexBuffer::~HardwareIndexBuffer()
{
    m_manager->_notifyIndexBufferDestroyed(this);
}

}
