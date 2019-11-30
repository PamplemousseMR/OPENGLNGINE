#pragma once

#include "Hardware/IHardwareBuffer.hpp"

#include <memory>

namespace Hardware
{

class HardwareBufferManager;
class HardwareVertexBuffer;

typedef std::shared_ptr<HardwareVertexBuffer> HardwareVertexBufferPtr;

class HardwareVertexBuffer final : public IHardwareBuffer
{

public:

    HardwareVertexBuffer(HardwareBufferManager* const, size_t, size_t, HARDWAREBUFFER_USAGE);
    virtual ~HardwareVertexBuffer() override final;

    inline size_t getVertexSizeInBytes() const;
    inline size_t getNumVertices() const;

private:

    HardwareVertexBuffer(const HardwareVertexBuffer&) = delete;
    HardwareVertexBuffer(HardwareVertexBuffer&&) = delete;
    HardwareVertexBuffer& operator=(const HardwareVertexBuffer&) = delete;
    HardwareVertexBuffer& operator=(HardwareVertexBuffer&&) = delete;

    size_t m_vertexSizeInBytes {0};
    size_t m_numVertices {0};

};

size_t HardwareVertexBuffer::getVertexSizeInBytes() const
{
    return m_vertexSizeInBytes;
}

size_t HardwareVertexBuffer::getNumVertices() const
{
    return m_numVertices;
}

}
