#include "OpenGLNgine/Render/SubMesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/Mesh.hpp"

namespace Render
{

void SubMesh::render() const
{
    if(m_dirty)
    {
        if(vertexData != nullptr)
        {
            vertexData->m_vertexDeclaration->lock();
            for(const auto& binding : vertexData->m_vertexBufferBinding->getBufferBindings())
            {
                const Hardware::HardwareVertexBufferPtr buffer = binding.second;
                buffer->lock();

                int stride = 0;

                const Hardware::VertexDeclaration::VertexElementList& elements = vertexData->m_vertexDeclaration->getElements();
                for(const Hardware::VertexElement& element : elements)
                {
                    if(element.m_source == binding.first)
                    {
                        stride += element.getTypeCount();
                    }
                }

                for(const Hardware::VertexElement& element : elements)
                {
                    if(element.m_source == binding.first)
                    {
                        const int offset = element.m_offsetInBytes + vertexData->m_vertexStart * buffer->m_vertexType;
                        GL::DataBuffer::setAttrib(element.m_semantic, element.getTypeCount(), element.getType(), false, buffer->m_vertexType*stride, offset);
                        GL::DataBuffer::setLocation(element.m_semantic);
                    }
                }
            }
            if(indexData != nullptr)
            {
                indexData->m_indexBuffer->lock();
            }
            vertexData->m_vertexDeclaration->unlock();
        }
        m_dirty = false;
    }

    vertexData->m_vertexDeclaration->lock();
    if(indexData != nullptr)
    {
        const int offset = indexData->m_indexStart * indexData->m_indexBuffer->m_indexType;
        GL::DrawCall::drawElements(vertexData->getRenderType(), indexData->m_indexCount, indexData->m_indexBuffer->getType(), offset);
    }
    else
    {
        GL::DrawCall::drawArrays(vertexData->getRenderType(), 0, vertexData->m_vertexCount);
    }
}

SubMesh::SubMesh(Mesh* const _mesh, const std::string& _name):
    IResource(_name),
    m_parent(_mesh)
{
    GLNGINE_ASSERT_IF(!_mesh, "The parent mesh mustn't be null");
}

SubMesh::~SubMesh()
{
}

}
