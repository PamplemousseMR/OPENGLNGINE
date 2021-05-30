#include "OpenGLNgine/Render/Mesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

SubMesh* Mesh::createSubMesh(const std::string& _name)
{
    SubMesh* ptr = new SubMesh(this, _name);
    m_subMeshes.insert(ptr);
    return ptr;
}

void Mesh::destroySubMesh(SubMesh* _subMesh)
{
    GLNGINE_ASSERT_IF(!_subMesh, "The sub mesh mustn't be null");

    m_subMeshes.erase(_subMesh);
    delete _subMesh;
}

void Mesh::destroyAllSubMeshes()
{
    SubMeshList::const_iterator itBeg, itEnd;
    itEnd = m_subMeshes.end();
    for(itBeg=m_subMeshes.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_subMeshes.clear();
}

void Mesh::setMaterial(::Hardware::MaterialPtr _material)
{
    SubMeshList::const_iterator itBeg, itEnd;
    itEnd = m_subMeshes.end();
    for(itBeg=m_subMeshes.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        (*itBeg)->material = _material;
    }
}


Mesh::Mesh(SceneManager* const _sceneManager, const std::string& _name):
    Component(_sceneManager, _name)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager mustn't be null");
}

Mesh::~Mesh()
{
    this->destroyAllSubMeshes();
}

}
