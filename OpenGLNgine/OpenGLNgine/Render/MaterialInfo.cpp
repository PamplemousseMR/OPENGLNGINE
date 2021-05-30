#include "OpenGLNgine/Render/MaterialInfo.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

TextureInfo* MaterialInfo::addTextureInfo(TEXTURE_TYPE _type)
{
    TextureInfoList::const_iterator it, itEnd;
    itEnd = m_textureInfos.end();
    for(it=m_textureInfos.begin() ; it!=itEnd ; ++it)
    {
        if((*it).second->m_type == _type)
        {
            delete it->second;
            m_textureInfos.erase(it);
            break;
        }
    }
    TextureInfo* textInfo = new TextureInfo(_type);
    m_textureInfos.emplace(_type, textInfo);
    return textInfo;
}

void MaterialInfo::removeAllTextureInfos()
{
    TextureInfoList::const_iterator it, itEnd;
    itEnd = m_textureInfos.end();
    for(it=m_textureInfos.begin() ; it!=itEnd ; ++it)
    {
        delete it->second;
        m_textureInfos.erase(it);
    }
    m_textureInfos.clear();
}

MaterialInfo::MaterialInfo(const std::string& _name):
    ::Core::IResource(_name)
{
}

MaterialInfo::~MaterialInfo()
{
    this->removeAllTextureInfos();
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
