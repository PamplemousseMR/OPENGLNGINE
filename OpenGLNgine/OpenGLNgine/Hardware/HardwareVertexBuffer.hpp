#pragma once

#include "OpenGLNgine/Hardware/IHardwareBuffer.hpp"

#include <memory>

namespace Hardware
{

enum HARDWAREVERTEXBUFFER_TYPE : int
{
    HT_FLOAT = sizeof(float)
};

class HardwareBufferManager;
class HardwareVertexBuffer;

typedef std::shared_ptr<HardwareVertexBuffer> HardwareVertexBufferPtr;

class HardwareVertexBuffer final : public IHardwareBuffer
{

public:

    HardwareVertexBuffer(HardwareBufferManager* const _manager, HARDWAREVERTEXBUFFER_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage);

    ~HardwareVertexBuffer() override;

    HardwareVertexBuffer(const HardwareVertexBuffer&) = delete;

    HardwareVertexBuffer(HardwareVertexBuffer&&) = delete;

    HardwareVertexBuffer& operator=(const HardwareVertexBuffer&) = delete;

    HardwareVertexBuffer& operator=(HardwareVertexBuffer&&) = delete;

    const HARDWAREVERTEXBUFFER_TYPE m_vertexType;

    const size_t m_numVertices;

};

}
