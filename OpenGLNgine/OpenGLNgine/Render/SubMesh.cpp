#include "OpenGLNgine/Render/SubMesh.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/Mesh.hpp"

namespace Render
{

SubMesh::SubMesh(Mesh* const _mesh, const std::string& _name):
    IResource(_name),
    m_parent(_mesh)
{
    GLNGINE_ASSERT_IF(!_mesh, "The parent mesh shall not be null");
}

SubMesh::~SubMesh()
{
}

}
