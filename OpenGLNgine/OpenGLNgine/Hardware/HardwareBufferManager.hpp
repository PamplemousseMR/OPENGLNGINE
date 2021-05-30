#pragma once

#include "OpenGLNgine/Hardware/HardwareIndexBuffer.hpp"
#include "OpenGLNgine/Hardware/HardwareVertexBuffer.hpp"
#include "OpenGLNgine/Hardware/IndexData.hpp"
#include "OpenGLNgine/Hardware/VertexData.hpp"

#include <set>

namespace Hardware
{

class HardwareBufferManager final
{

    friend HardwareVertexBuffer;
    friend HardwareIndexBuffer;

public:

    static HardwareBufferManager& getInstance();

    HardwareBufferManager(const HardwareBufferManager&) = delete;

    HardwareBufferManager(HardwareBufferManager&&) = delete;

    HardwareBufferManager& operator=(const HardwareBufferManager&) = delete;

    HardwareBufferManager& operator=(HardwareBufferManager&&) = delete;

    HardwareIndexBufferPtr createIndexBuffer(INDEX_TYPE _type, size_t _size, HARDWAREBUFFER_USAGE _usage);

    HardwareVertexBufferPtr createVertexBuffer(VERTEX_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage);

    VertexData* createVertexData();

    IndexData* createIndexData();

    void destroyVertexData(VertexData* _data);

    void destroyIndexData(IndexData* _data);

    void destroyAllVertexData();

    void destroyAllIndexData();

private:

    typedef std::set<VertexData*> VertexDataList;

    typedef std::set<IndexData*> IndexDataList;

    typedef std::set<HardwareIndexBuffer*> IndexBufferList;

    typedef std::set<HardwareVertexBuffer*> VertexBufferList;

    struct Initializer final
    {
        Initializer();

        ~Initializer();
    };

    static HardwareBufferManager* s_instance;

    HardwareBufferManager();

    ~HardwareBufferManager();

    void _notifyIndexBufferDestroyed(HardwareIndexBuffer* _indexBuffer);

    void _notifyVertexBufferDestroyed(HardwareVertexBuffer* _vertexBuffer);

    VertexDataList m_vertexData {};

    IndexDataList m_indexData {};

    IndexBufferList m_indexBuffers {};

    VertexBufferList m_vertexBuffers {};

};

}
