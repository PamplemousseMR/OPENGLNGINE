#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"

namespace Hardware
{

HardwareBufferManager* HardwareBufferManager::s_instance = nullptr;

HardwareBufferManager& HardwareBufferManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

HardwareIndexBufferPtr HardwareBufferManager::createIndexBuffer(INDEX_TYPE _type, size_t _size, HARDWAREBUFFER_USAGE _usage)
{
    HardwareIndexBuffer* ptr = new HardwareIndexBuffer(this, _type, _size, _usage);
    m_indexBuffers.insert(ptr);
    return HardwareIndexBufferPtr(ptr);
}

HardwareVertexBufferPtr HardwareBufferManager::createVertexBuffer(VERTEX_TYPE _type, size_t _numVertices, HARDWAREBUFFER_USAGE _usage)
{
    HardwareVertexBuffer* ptr = new HardwareVertexBuffer(this, _type, _numVertices, _usage);
    m_vertexBuffers.insert(ptr);
    return HardwareVertexBufferPtr(ptr);
}

VertexData* HardwareBufferManager::createVertexData()
{
    VertexData* ptr = new VertexData(this);
    m_vertexData.insert(ptr);
    return ptr;
}

IndexData* HardwareBufferManager::createIndexData()
{
    IndexData* ptr = new IndexData();
    m_indexData.insert(ptr);
    return ptr;
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

void HardwareBufferManager::destroyVertexData(VertexData* _data)
{
    GLNGINE_ASSERT_IF(!_data, "The vertex data mustn't be null");

    m_vertexData.erase(_data);
    delete _data;
}

void HardwareBufferManager::destroyIndexData(IndexData* _data)
{
    GLNGINE_ASSERT_IF(!_data, "The index data mustn't be null");

    m_indexData.erase(_data);
    delete _data;
}

void HardwareBufferManager::destroyVertexBufferBinding(VertexBufferBinding* _binding)
{
    GLNGINE_ASSERT_IF(!_binding, "The vertex buffer binding mustn't be null");

    m_vertexBufferBindings.erase(_binding);
    delete _binding;
}

void HardwareBufferManager::destroyVertexDeclaration(VertexDeclaration* _declaration)
{
    GLNGINE_ASSERT_IF(!_declaration, "The vertex declaration mustn't be null");

    m_vertexDeclarations.erase(_declaration);
    delete _declaration;
}

void HardwareBufferManager::destroyAllVertexData()
{
    VertexDataList::const_iterator itBeg, itEnd;
    itEnd = m_vertexData.end();
    for(itBeg=m_vertexData.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_vertexData.clear();
}

void HardwareBufferManager::destroyAllIndexData()
{
    IndexDataList::const_iterator itBeg, itEnd;
    itEnd = m_indexData.end();
    for(itBeg=m_indexData.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_vertexData.clear();
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
    GLNGINE_ASSERT_IF(!_indexBuffer, "The hardware index buffer mustn't be null");

    IndexBufferList::const_iterator it = std::find(m_indexBuffers.begin(), m_indexBuffers.end(), _indexBuffer);
    if(it == m_indexBuffers.end())
    {
        GLNGINE_EXCEPTION("The index buffer doesn't exists");
    }
    m_indexBuffers.erase(it);
}

void HardwareBufferManager::_notifyVertexBufferDestroyed(HardwareVertexBuffer* _vertexBuffer)
{
    GLNGINE_ASSERT_IF(!_vertexBuffer, "The hardware vertex buffer mustn't be null");

    VertexBufferList::const_iterator it = std::find(m_vertexBuffers.begin(), m_vertexBuffers.end(), _vertexBuffer);
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
    this->destroyAllVertexBufferBinding();
    this->destroyAllVertexDeclaration();

    m_vertexBuffers.clear();
    m_indexBuffers.clear();
}

}
