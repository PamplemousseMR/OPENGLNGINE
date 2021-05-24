#pragma once

#include "OpenGLNgine/Hardware/IHardwareBuffer.hpp"

#include <memory>

namespace Hardware
{

enum INDEX_TYPE : int
{
    IT_UNSIGNED_BYTE = sizeof(unsigned char),
    IT_UNSIGNED_SHORT = sizeof(unsigned short),
    IT_UNSIGNED_INT = sizeof(unsigned int)
};

class HardwareBufferManager;
class HardwareIndexBuffer;

typedef std::shared_ptr<HardwareIndexBuffer> HardwareIndexBufferPtr;

class HardwareIndexBuffer final : public IHardwareBuffer
{

public:

    static GL::DATABUFFER_TYPE getType(INDEX_TYPE _type);

    HardwareIndexBuffer(HardwareBufferManager* const _manager, INDEX_TYPE _type, size_t _numIndex, HARDWAREBUFFER_USAGE _usage);

    ~HardwareIndexBuffer() override;

    HardwareIndexBuffer(const HardwareIndexBuffer&) = delete;

    HardwareIndexBuffer(HardwareIndexBuffer&&) = delete;

    HardwareIndexBuffer& operator=(const HardwareIndexBuffer&) = delete;

    HardwareIndexBuffer& operator=(HardwareIndexBuffer&&) = delete;

    inline GL::DATABUFFER_TYPE getType() const;

    const INDEX_TYPE m_indexType;

    const size_t m_numIndex;

};

inline GL::DATABUFFER_TYPE HardwareIndexBuffer::getType() const
{
    return HardwareIndexBuffer::getType(m_indexType);
}

}
