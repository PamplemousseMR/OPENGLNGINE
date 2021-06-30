#include "OpenGLNgine/Render/SubMesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Core/IHardwareManager.hpp"
#include "OpenGLNgine/Render/Mesh.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

void SubMesh::setMaterial(::Hardware::MaterialPtr _material)
{
    GLNGINE_ASSERT_IF(_material->m_manager->m_renderWindow != m_parent->getSceneManager()->getRenderWindow(), "The material doe not came from this context");

    m_material = _material;
}

SubMesh::SubMesh(Mesh* const _parent, const std::string& _name) :
    IResource(_name),
    m_parent(_parent)
{
    GLNGINE_ASSERT_IF(!_parent, "The parent mesh shall not be null");
}

SubMesh::~SubMesh()
{
}

}
