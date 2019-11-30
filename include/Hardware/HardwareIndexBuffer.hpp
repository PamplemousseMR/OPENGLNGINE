#pragma once

#include "Hardware/IHardwareBuffer.hpp"

#include <memory>

namespace Hardware
{

class HardwareBufferManager;
class HardwareIndexBuffer;

typedef std::shared_ptr<HardwareIndexBuffer> HardwareIndexBufferPtr;

class HardwareIndexBuffer final : public IHardwareBuffer
{

public:

    enum INDEX_TYPE
    {
        IT_UNSIGNED_BYTE = sizeof(unsigned char),
        IT_UNSIGNED_SHORT = sizeof(unsigned short),
        IT_UNSIGNED_INT = sizeof(unsigned int)
    };

    HardwareIndexBuffer(HardwareBufferManager* const, INDEX_TYPE, size_t, USAGE);
    virtual ~HardwareIndexBuffer() override final;

    inline INDEX_TYPE getIndexType() const;
    inline size_t getNumIndex() const;

private:

    HardwareIndexBuffer(const HardwareIndexBuffer&) = delete;
    HardwareIndexBuffer(HardwareIndexBuffer&&) = delete;
    HardwareIndexBuffer& operator=(const HardwareIndexBuffer&) = delete;
    HardwareIndexBuffer& operator=(HardwareIndexBuffer&&) = delete;

    INDEX_TYPE m_indexType {IT_UNSIGNED_INT};
    size_t m_numIndex {0};

};


HardwareIndexBuffer::INDEX_TYPE HardwareIndexBuffer::getIndexType() const
{
    return m_indexType;
}

size_t HardwareIndexBuffer::getNumIndex() const
{
    return m_numIndex;
}

}
