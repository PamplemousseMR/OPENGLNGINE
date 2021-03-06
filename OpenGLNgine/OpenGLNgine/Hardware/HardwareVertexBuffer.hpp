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

    friend HardwareBufferManager;

public:

    ~HardwareVertexBuffer() override;

    HardwareVertexBuffer(const HardwareVertexBuffer&) = delete;

    HardwareVertexBuffer(HardwareVertexBuffer&&) = delete;

    HardwareVertexBuffer& operator=(const HardwareVertexBuffer&) = delete;

    HardwareVertexBuffer& operator=(HardwareVertexBuffer&&) = delete;

    const HARDWAREVERTEXBUFFER_TYPE m_vertexType;

    const size_t m_numVertices;

private:

    HardwareVertexBuffer(HardwareBufferManager* const _manager, const std::string& _name, HARDWAREVERTEXBUFFER_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage);

};

}
