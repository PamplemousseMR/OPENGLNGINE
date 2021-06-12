#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

#include <algorithm>

namespace Hardware
{

HardwareBufferManager* HardwareBufferManager::s_instance = nullptr;

HardwareBufferManager& HardwareBufferManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

HardwareIndexBufferPtr HardwareBufferManager::createIndexBuffer(HARDWREINDEXBUFFER_TYPE _type, size_t _size, HARDWAREBUFFER_USAGE _usage)
{
    HardwareIndexBuffer* const ptr = new HardwareIndexBuffer(this, _type, _size, _usage);
    m_indexBuffers.insert(ptr);
    return HardwareIndexBufferPtr(ptr);
}

HardwareVertexBufferPtr HardwareBufferManager::createVertexBuffer(HARDWAREVERTEXBUFFER_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage)
{
    HardwareVertexBuffer* const ptr = new HardwareVertexBuffer(this, _type, _numVertices, _usage);
    m_vertexBuffers.insert(ptr);
    return HardwareVertexBufferPtr(ptr);
}

VertexData* HardwareBufferManager::createVertexData()
{
    VertexData* const ptr = new VertexData(this);
    m_vertexData.insert(ptr);
    return ptr;
}

IndexData* HardwareBufferManager::createIndexData()
{
    IndexData* const ptr = new IndexData();
    m_indexData.insert(ptr);
    return ptr;
}

void HardwareBufferManager::destroyAllVertexData()
{
    VertexDataList::const_iterator itBeg = m_vertexData.begin();
    const VertexDataList::const_iterator itEnd = m_vertexData.end();
    for(; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_vertexData.clear();
}

void HardwareBufferManager::destroyAllIndexData()
{
    IndexDataList::const_iterator itBeg = m_indexData.begin();
    const IndexDataList::const_iterator itEnd = m_indexData.end();
    for(; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_vertexData.clear();
}

void HardwareBufferManager::_notifyIndexBufferDestroyed(const HardwareIndexBuffer* _indexBuffer)
{
    GLNGINE_ASSERT_IF(!_indexBuffer, "The hardware index buffer mustn't be null");

    const IndexBufferList::const_iterator it = std::find(m_indexBuffers.begin(), m_indexBuffers.end(), _indexBuffer);
    if(it == m_indexBuffers.end())
    {
        GLNGINE_EXCEPTION("The index buffer doesn't exists");
    }
    m_indexBuffers.erase(it);
}

void HardwareBufferManager::_notifyVertexBufferDestroyed(const HardwareVertexBuffer* _vertexBuffer)
{
    GLNGINE_ASSERT_IF(!_vertexBuffer, "The hardware vertex buffer mustn't be null");

    const VertexBufferList::const_iterator it = std::find(m_vertexBuffers.begin(), m_vertexBuffers.end(), _vertexBuffer);
    if(it == m_vertexBuffers.end())
    {
        GLNGINE_EXCEPTION("The vertex buffer doesn't exists");
    }    m_vertexBuffers.erase(it);
}

HardwareBufferManager::Initializer::Initializer()
{
    HardwareBufferManager::s_instance = new HardwareBufferManager();
}

HardwareBufferManager::Initializer::~Initializer()
{
    delete HardwareBufferManager::s_instance;
    HardwareBufferManager::s_instance = nullptr;
}

HardwareBufferManager::HardwareBufferManager()
{
}

HardwareBufferManager::~HardwareBufferManager()
{
    this->destroyAllVertexData();
    this->destroyAllIndexData();

    m_vertexBuffers.clear();
    m_indexBuffers.clear();
}

}
