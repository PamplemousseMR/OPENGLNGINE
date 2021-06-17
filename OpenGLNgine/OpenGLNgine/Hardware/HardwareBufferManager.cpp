#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

#include <algorithm>

namespace Hardware
{

HardwareIndexBufferPtr HardwareBufferManager::createIndexBuffer(const std::string& _name, HARDWREINDEXBUFFER_TYPE _type, size_t _size, HARDWAREBUFFER_USAGE _usage)
{
    const HardwareIndexBufferPtr ptr(new HardwareIndexBuffer(this, _name,  _type, _size, _usage));
    this->add(ptr);
    return ptr;
}

HardwareVertexBufferPtr HardwareBufferManager::createVertexBuffer(const std::string& _name, HARDWAREVERTEXBUFFER_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage)
{
    const HardwareVertexBufferPtr ptr(new HardwareVertexBuffer(this, _name, _type, _numVertices, _usage));
    this->add(ptr);
    return ptr;
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

HardwareBufferManager::HardwareBufferManager()
{
}

HardwareBufferManager::~HardwareBufferManager()
{
    this->destroyAllVertexData();
    this->destroyAllIndexData();
}

}
