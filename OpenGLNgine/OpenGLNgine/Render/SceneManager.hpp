#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Render/Camera.hpp"
#include "OpenGLNgine/Render/Light.hpp"
#include "OpenGLNgine/Render/Mesh.hpp"
#include "OpenGLNgine/Render/SceneNode.hpp"

#include <map>
#include <string>

namespace Render
{

class Render;

class SceneManager final : public ::Core::IResource
{

    friend Camera;
    friend Render;

public:

    typedef std::map< std::string, Mesh* > MeshList;

    typedef std::map< std::string, Light* > LightList;

    SceneManager(const SceneManager&) = delete;

    SceneManager(SceneManager&&) = delete;

    SceneManager& operator=(const SceneManager&) = delete;

    SceneManager& operator=(SceneManager&&) = delete;

    inline SceneNode* getRootSceneNode() const;

    Camera* createCamera(const std::string& _name);

    void destroyCamera(const Camera* const _camera);

    void destroyAllCameras();

    Mesh* createMesh(const std::string& _name);

    void destroyMesh(const Mesh* const _mesh);

    void destroyAllMeshs();

    inline const MeshList& getMeshes() const;

    Light* createLight(const std::string& _name);

    void destroyLight(const Light* const _light);

    void destroyAllLights();

    inline const LightList& getLights() const;

private:

    typedef std::map< std::string, Camera* > CameraList;

    SceneManager(Render* const _render, const std::string& _name);

    ~SceneManager();

    Render* const m_render;

    CameraList m_cameras {};

    MeshList m_meshes {};

    LightList m_lights {};

    SceneNode* const m_rootSceneNode;

};


inline SceneNode* SceneManager::getRootSceneNode() const
{
    return m_rootSceneNode;
}

inline const SceneManager::MeshList& SceneManager::getMeshes() const
{
    return m_meshes;
}

inline const SceneManager::LightList& SceneManager::getLights() const
{
    return m_lights;
}

}
