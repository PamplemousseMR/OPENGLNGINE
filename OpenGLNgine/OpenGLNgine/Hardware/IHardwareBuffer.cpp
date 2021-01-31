#include "OpenGLNgine/Hardware/IHardwareBuffer.hpp"

#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

void IHardwareBuffer::writeData(size_t _offset, size_t _sizeInBytes, const void* _src, bool _discard)
{
    m_dataBuffer.bind();
    if(_offset == 0 && _sizeInBytes == m_sizeInBytes)
    {
        m_dataBuffer.writeData(m_sizeInBytes, _src, getUsage(m_usage));
    }
    else
    {
        if(_discard)
        {
            m_dataBuffer.writeData(m_sizeInBytes, nullptr, getUsage(m_usage));
        }

        m_dataBuffer.writeData(_offset, _sizeInBytes, _src);
    }
}

IHardwareBuffer::IHardwareBuffer(HardwareBufferManager* const _manager, GL::DATABUFFER_TARGET _target, size_t _sizeInBytes, HARDWAREBUFFER_USAGE _usage):
    m_manager(_manager),
    m_dataBuffer(_target),
    m_sizeInBytes(_sizeInBytes),
    m_usage(_usage)
{
    GLNGINE_ASSERT_IF(!_manager, "The hardware buffer manager mustn't be null");
    m_dataBuffer.bind();
    m_dataBuffer.writeData(m_sizeInBytes, nullptr, getUsage(m_usage));
}

IHardwareBuffer::~IHardwareBuffer()
{
}

GL::DATABUFFER_USAGE IHardwareBuffer::getUsage(HARDWAREBUFFER_USAGE _usage)
{
    switch(_usage)
    {
    case HU_STREAM_DRAW:
        return GL::DATABUFFER_USAGE::DT_STREAM_DRAW;
    case HU_STREAM_READ:
        return GL::DATABUFFER_USAGE::DT_STREAM_READ;
    case HU_STREAM_COPY:
        return GL::DATABUFFER_USAGE::DT_STREAM_COPY;
    case HU_STATIC_DRAW:
        return GL::DATABUFFER_USAGE::DT_STATIC_DRAW;
    case HU_STATIC_READ:
        return GL::DATABUFFER_USAGE::DT_STATIC_READ;
    case HU_STATIC_COPY:
        return GL::DATABUFFER_USAGE::DT_STATIC_COPY;
    case HU_DYNAMIC_DRAW:
        return GL::DATABUFFER_USAGE::DT_DYNAMIC_DRAW;
    case HU_DYNAMIC_READ:
        return GL::DATABUFFER_USAGE::DT_DYNAMIC_READ;
    case HU_DYNAMIC_COPY:
        return GL::DATABUFFER_USAGE::DT_DYNAMIC_COPY;
    default:
        GLNGINE_EXCEPTION("Unhandle buffer usage");
    }
}

}
