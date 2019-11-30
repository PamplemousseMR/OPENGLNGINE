#include "Hardware/HardwareBufferManager.hpp"

#include <cassert>

namespace Hardware
{

HardwareBufferManager* HardwareBufferManager::s_INSTANCE = nullptr;

HardwareBufferManager& HardwareBufferManager::getInstance()
{
    HardwareBufferManager* instance = HardwareBufferManager::getInstancePtr();
    return *instance;
}

HardwareBufferManager* HardwareBufferManager::getInstancePtr()
{
    const static MemGuard memGuard;
    if(!s_INSTANCE)
    {
        s_INSTANCE = new HardwareBufferManager();
    }
    return s_INSTANCE;
}

HardwareBufferManager::HardwareBufferManager()
{
}

HardwareBufferManager::~HardwareBufferManager()
{
    m_vertexBuffers.clear();
    m_indexBuffers.clear();

    this->destroyAllVertexBufferBinding();
    this->destroyAllVertexDeclaration();
}

HardwareIndexBufferPtr HardwareBufferManager::createIndexBuffer(HardwareIndexBuffer::INDEX_TYPE _type, size_t _size, IHardwareBuffer::USAGE _usage)
{
    HardwareIndexBuffer* ptr = new HardwareIndexBuffer(this, _type, _size, _usage);
    m_indexBuffers.insert(ptr);
    return HardwareIndexBufferPtr(ptr);
}

HardwareVertexBufferPtr HardwareBufferManager::createVertexBuffer(size_t _vertexSizeInBytes, size_t _numVertices, IHardwareBuffer::USAGE _usage)
{
    HardwareVertexBuffer* ptr = new HardwareVertexBuffer(this, _vertexSizeInBytes, _numVertices, _usage);
    m_vertexBuffers.insert(ptr);
    return HardwareVertexBufferPtr(ptr);
}

VertexBufferBinding* HardwareBufferManager::createVertexBufferBinding()
{
    VertexBufferBinding* ptr = new VertexBufferBinding();
    m_vertexBufferBindings.insert(ptr);
    return ptr;
}

VertexDeclaration* HardwareBufferManager::createVertexDeclaration()
{
    VertexDeclaration* ptr = new VertexDeclaration();
    m_vertexDeclarations.insert(ptr);
    return ptr;
}

void HardwareBufferManager::destroyVertexBufferBinding(VertexBufferBinding* _binding)
{
    m_vertexBufferBindings.erase(_binding);
    delete _binding;
}

void HardwareBufferManager::destroyVertexDeclaration(VertexDeclaration* _declaration)
{
    m_vertexDeclarations.erase(_declaration);
    delete _declaration;
}

void HardwareBufferManager::destroyAllVertexBufferBinding()
{
    VertexBufferBindingList::const_iterator itBeg, itEnd;
    itEnd = m_vertexBufferBindings.end();
    for(itBeg=m_vertexBufferBindings.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_vertexBufferBindings.clear();
}

void HardwareBufferManager::destroyAllVertexDeclaration()
{
    VertexDeclarationList::const_iterator itBeg, itEnd;
    itEnd = m_vertexDeclarations.end();
    for(itBeg=m_vertexDeclarations.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_vertexDeclarations.clear();
}

void HardwareBufferManager::_notifyIndexBufferDestroyed(HardwareIndexBuffer* _indexBuffer)
{
    IndexBufferList::const_iterator ibIt = std::find(m_indexBuffers.begin(), m_indexBuffers.end(), _indexBuffer);
    assert(ibIt != m_indexBuffers.end() && "The index buffer doesn't exist");
    m_indexBuffers.erase(ibIt);
}

void HardwareBufferManager::_notifyVertexBufferDestroyed(HardwareVertexBuffer* _vertexBuffer)
{
    VertexBufferList::const_iterator vbIt = std::find(m_vertexBuffers.begin(), m_vertexBuffers.end(), _vertexBuffer);
    assert(vbIt != m_vertexBuffers.end() && "The vertex buffer doesn't exist");
    m_vertexBuffers.erase(vbIt);
}


}
