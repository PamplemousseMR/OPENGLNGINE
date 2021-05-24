#include "OpenGLNgine/Render/SceneManager.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/Render.hpp"

namespace Render
{

Camera* SceneManager::createCamera(const std::string& _name)
{
    if(m_cameras.find(_name) != m_cameras.end())
    {
        GLNGINE_EXCEPTION("A camera with the name '" + _name + "' already exists");
    }

    Camera* camera = new Camera(this, _name);
    m_cameras.emplace(_name, camera);
    return camera;
}

void SceneManager::destroyCamera(const Camera* const _camera)
{
    GLNGINE_ASSERT_IF(!_camera, "The camera mustn't be null");

    CameraList::const_iterator it = m_cameras.find(_camera->getName());
    if(it == m_cameras.end())
    {
        GLNGINE_EXCEPTION("A camera with the name '" + _camera->getName() + "' doesn't exists");
    }

    m_cameras.erase(it);
    delete _camera;
}

void SceneManager::destroyAllCameras()
{
    CameraList::iterator it = m_cameras.begin();
    while(it != m_cameras.end())
    {
        this->destroyCamera(it->second);
        it = m_cameras.begin();
    }
}

Mesh* SceneManager::createMesh(const std::string& _name)
{
    if(m_meshes.find(_name) != m_meshes.end())
    {
        GLNGINE_EXCEPTION("A mesh with the name '" + _name + "' already exists");
    }

    Mesh* mesh = new Mesh(this, _name);
    m_meshes.emplace(_name, mesh);
    return mesh;
}

void SceneManager::destroyMesh(const Mesh* const _mesh)
{
    GLNGINE_ASSERT_IF(!_mesh, "The mesh mustn't be null");

    MeshList::const_iterator it = m_meshes.find(_mesh->getName());
    if(it == m_meshes.end())
    {
        GLNGINE_EXCEPTION("A mesh with the name '" + _mesh->getName() + "' doesn't exists");
    }

    m_meshes.erase(it);
    delete _mesh;
}

void SceneManager::destroyAllMeshs()
{
    MeshList::iterator it = m_meshes.begin();
    while(it != m_meshes.end())
    {
        this->destroyMesh(it->second);
        it = m_meshes.begin();
    }
}

SceneManager::SceneManager(Render* const _render, const std::string& _name):
    IResource(_name),
    m_render(_render),
    m_rootSceneNode(new SceneNode(this))
{
    GLNGINE_ASSERT_IF(!_render, "The render mustn't be null");
}

SceneManager::~SceneManager()
{
    this->destroyAllCameras();
    this->destroyAllMeshs();
    delete m_rootSceneNode;
}

}
