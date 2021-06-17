#pragma once

#include "OpenGLNgine/Core/IHardwareResource.hpp"
#include "OpenGLNgine/GL/DataBuffer.hpp"

namespace Hardware
{

/// Manages all expected usage pattern of the data store.
enum HARDWAREBUFFER_USAGE
{
    HU_STREAM_DRAW,
    HU_STREAM_READ,
    HU_STREAM_COPY,
    HU_STATIC_DRAW,
    HU_STATIC_READ,
    HU_STATIC_COPY,
    HU_DYNAMIC_DRAW,
    HU_DYNAMIC_READ,
    HU_DYNAMIC_COPY
};

class HardwareBufferManager;

class IHardwareBuffer : public ::Core::IHardwareResource
{

public:

    IHardwareBuffer(const IHardwareBuffer&) = delete;

    IHardwareBuffer(IHardwareBuffer&&) = delete;

    IHardwareBuffer& operator=(const IHardwareBuffer&) = delete;

    IHardwareBuffer& operator=(IHardwareBuffer&&) = delete;

    inline size_t getSizeInBytes() const;

    inline void lock();

    inline void unlock();

    void writeData(size_t _offset, size_t _sizeInBytes, const void* _src, bool _discard);

protected:

    IHardwareBuffer(HardwareBufferManager* const _manager, const std::string& _name, ::GL::DATABUFFER_TARGET _target, size_t _sizeInBytes, HARDWAREBUFFER_USAGE _usage);

    virtual ~IHardwareBuffer();

    HardwareBufferManager* const m_manager;

private:

    static ::GL::DATABUFFER_USAGE getUsage(HARDWAREBUFFER_USAGE _usage);

    ::GL::DataBuffer m_dataBuffer;

    const size_t m_sizeInBytes;

    const HARDWAREBUFFER_USAGE m_usage;

};

inline size_t IHardwareBuffer::getSizeInBytes() const
{
    return m_sizeInBytes;
}

inline void IHardwareBuffer::lock()
{
    m_dataBuffer.bind();
}

inline void IHardwareBuffer::unlock()
{
    m_dataBuffer.unbind();
}

}
