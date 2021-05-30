#include "OpenGLNgine/Render/SubMesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/Mesh.hpp"

namespace Render
{

void SubMesh::setMaterialInfo(MaterialInfo* const _matInfo)
{
    if(m_materialInfo != nullptr)
    {
        m_materialInfo->_notifySubMeshRemoved(this);
    }
    m_materialInfo = _matInfo;
    m_materialInfo->_notifySubMeshAdded(this);
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

void SubMesh::_notifyMaterialInfoDestroyed()
{
    m_materialInfo = nullptr;
}

}
