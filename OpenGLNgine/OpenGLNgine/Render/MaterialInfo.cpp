#include "OpenGLNgine/Render/MaterialInfo.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

MaterialInfo::MaterialInfo(const std::string& _name):
    ::Core::IResource(_name)
{
}

MaterialInfo::~MaterialInfo()
{
    for(auto& subMesh : m_subMeshes)
    {
        subMesh.second->_notifyMaterialInfoDestroyed();
    }
}

void MaterialInfo::_notifySubMeshAdded(SubMesh* const _subMesh)
{
    if(m_subMeshes.find(_subMesh->getName()) != m_subMeshes.end())
    {
        GLNGINE_EXCEPTION("A submesh with the name '" + _subMesh->getName() + "' already exists");
    }
    m_subMeshes.emplace(_subMesh->getName(), _subMesh);
}

void MaterialInfo::_notifySubMeshRemoved(SubMesh* const _subMesh)
{
    SubMeshList::const_iterator it = m_subMeshes.find(_subMesh->getName());
    if(it == m_subMeshes.end())
    {
        GLNGINE_EXCEPTION("A submesh with the name '" + _subMesh->getName() + "' doesn't exists");
    }
    m_subMeshes.erase(it);
}

}
