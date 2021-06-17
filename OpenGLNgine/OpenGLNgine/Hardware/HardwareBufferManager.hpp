#pragma once

#include "OpenGLNgine/Core/IHardwareManager.hpp"
#include "OpenGLNgine/Hardware/HardwareIndexBuffer.hpp"
#include "OpenGLNgine/Hardware/HardwareVertexBuffer.hpp"
#include "OpenGLNgine/Hardware/IndexData.hpp"
#include "OpenGLNgine/Hardware/VertexData.hpp"

#include <set>

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class HardwareBufferManager final :
        public ::Core::IHardwareManager
{

    friend ::Render::RenderWindow;

public:

    HardwareBufferManager(const HardwareBufferManager&) = delete;

    HardwareBufferManager(HardwareBufferManager&&) = delete;

    HardwareBufferManager& operator=(const HardwareBufferManager&) = delete;

    HardwareBufferManager& operator=(HardwareBufferManager&&) = delete;

    HardwareIndexBufferPtr createIndexBuffer(const std::string& _name, HARDWREINDEXBUFFER_TYPE _type, size_t _size, HARDWAREBUFFER_USAGE _usage);

    HardwareVertexBufferPtr createVertexBuffer(const std::string& _name, HARDWAREVERTEXBUFFER_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage);

    VertexData* createVertexData();

    IndexData* createIndexData();

    void destroyAllVertexData();

    void destroyAllIndexData();

private:

    typedef std::set<VertexData*> VertexDataList;

    typedef std::set<IndexData*> IndexDataList;

    HardwareBufferManager();

    ~HardwareBufferManager();

    VertexDataList m_vertexData {};

    IndexDataList m_indexData {};

};

}
