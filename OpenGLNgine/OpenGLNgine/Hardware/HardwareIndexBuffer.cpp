#include "OpenGLNgine/Hardware/HardwareIndexBuffer.hpp"

#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

::GL::DATABUFFER_TYPE HardwareIndexBuffer::getType(HARDWREINDEXBUFFER_TYPE _type)
{
    switch(_type)
    {
    case HT_UNSIGNED_BYTE:
        return ::GL::DT_UNSIGNED_BYTE;
    case HT_UNSIGNED_SHORT:
        return ::GL::DT_UNSIGNED_SHORT;
    case HT_UNSIGNED_INT:
        return ::GL::DT_UNSIGNED_INT;
    default:
        GLNGINE_EXCEPTION("Unhandle index type");
    }
}

HardwareIndexBuffer::HardwareIndexBuffer(HardwareBufferManager* const _manager, const std::string& _name, HARDWREINDEXBUFFER_TYPE _type, size_t _numIndex, HARDWAREBUFFER_USAGE _usage):
    IHardwareBuffer(_manager, _name, ::GL::DT_ELEMENT, _type*_numIndex, _usage),
    m_indexType(_type),
    m_numIndex(_numIndex)
{
}

HardwareIndexBuffer::~HardwareIndexBuffer()
{
}

}
