#pragma once

#include <GL/glew.h>

namespace Hardware
{

class HardwareBufferManager;

class IHardwareBuffer
{

public:

    enum USAGE
    {
        U_STREAM_DRAW = GL_STREAM_DRAW,
        U_STREAM_READ = GL_STREAM_READ,
        U_STREAM_COPY = GL_STREAM_COPY,
        U_STATIC_DRAW = GL_STATIC_DRAW,
        U_STATIC_READ = GL_STATIC_READ,
        U_STATIC_COPY = GL_STATIC_COPY,
        U_DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
        U_DYNAMIC_READ = GL_DYNAMIC_READ,
        U_DYNAMIC_COPY = GL_DYNAMIC_COPY
    };

    inline USAGE getUsage() const;
    inline size_t getSizeInBytes() const;

    void lock();
    void unlock();

    void readData(size_t, size_t, void*);
    void writeData(size_t, size_t, const void*, bool);
    void copyData(const IHardwareBuffer&, size_t, size_t, size_t, bool);

protected:

    IHardwareBuffer(HardwareBufferManager* const, GLenum, size_t, USAGE);
    virtual ~IHardwareBuffer();

    HardwareBufferManager* const m_manager;

private:

    IHardwareBuffer(const IHardwareBuffer&) = delete;
    IHardwareBuffer(IHardwareBuffer&&) = delete;
    IHardwareBuffer& operator=(const IHardwareBuffer&) = delete;
    IHardwareBuffer& operator=(IHardwareBuffer&&) = delete;

    GLuint m_id;
    GLenum m_target;
    size_t m_sizeInBytes {0};
    const USAGE m_usage {U_STATIC_DRAW};

};

IHardwareBuffer::USAGE IHardwareBuffer::getUsage() const
{
    return m_usage;
}

size_t IHardwareBuffer::getSizeInBytes() const
{
    return m_sizeInBytes;
}

}
