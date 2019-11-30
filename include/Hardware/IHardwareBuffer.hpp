#pragma once

#include <GL/glew.h>

namespace Hardware
{

class HardwareBufferManager;

class IHardwareBuffer
{

public:

    enum HARDWAREBUFFER_USAGE
    {
        HBU_STREAM_DRAW = GL_STREAM_DRAW,
        HBU_STREAM_READ = GL_STREAM_READ,
        HBU_STREAM_COPY = GL_STREAM_COPY,
        HBU_STATIC_DRAW = GL_STATIC_DRAW,
        HBU_STATIC_READ = GL_STATIC_READ,
        HBU_STATIC_COPY = GL_STATIC_COPY,
        HBU_DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        HBU_DYNAMIC_READ = GL_DYNAMIC_READ,
        HBU_DYNAMIC_COPY = GL_DYNAMIC_COPY
    };

    inline HARDWAREBUFFER_USAGE getUsage() const;
    inline size_t getSizeInBytes() const;

    void lock();
    void unlock();

    void readData(size_t, size_t, void*);
    void writeData(size_t, size_t, const void*, bool);
    void copyData(const IHardwareBuffer&, size_t, size_t, size_t, bool);

protected:

    IHardwareBuffer(HardwareBufferManager* const, GLenum, size_t, HARDWAREBUFFER_USAGE);
    virtual ~IHardwareBuffer();

    HardwareBufferManager* const m_manager;

private:

    IHardwareBuffer(const IHardwareBuffer&) = delete;
    IHardwareBuffer(IHardwareBuffer&&) = delete;
    IHardwareBuffer& operator=(const IHardwareBuffer&) = delete;
    IHardwareBuffer& operator=(IHardwareBuffer&&) = delete;

    GLuint m_id;
    const GLenum m_target;
    const size_t m_sizeInBytes;
    const HARDWAREBUFFER_USAGE m_usage;

};

IHardwareBuffer::HARDWAREBUFFER_USAGE IHardwareBuffer::getUsage() const
{
    return m_usage;
}

size_t IHardwareBuffer::getSizeInBytes() const
{
    return m_sizeInBytes;
}

}
