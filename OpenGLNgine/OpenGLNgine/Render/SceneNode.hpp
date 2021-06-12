#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Render/Mesh.hpp"

#include <glm/glm.hpp>

#include <map>
#include <string>

namespace Render
{

class SceneManager;

class SceneNode final : public ::Core::IResource
{

    friend SceneManager;

public:

    typedef std::map< std::string, Mesh* > MeshList;

    typedef std::map< std::string, SceneNode* > SceneNodeList;

    SceneNode(const SceneNode&) = delete;

    SceneNode(SceneNode&&) = delete;

    SceneNode& operator=(const SceneNode&) = delete;

    SceneNode& operator=(SceneNode&&) = delete;

    SceneNode* createChild(const std::string& _name);

    inline const SceneNodeList& getChildren() const;

    void removeAndDestroyChild(SceneNode* const _child);

    void removeAndDestroyAllChildren();

    void attach(Mesh* const _mesh);

    void dettach(Mesh* const _mesh);

    void dettachAll();

    void setOrientation(const ::glm::vec3& _orientation);

    inline ::glm::vec3 getOrientation() const;

    void setPosition(const ::glm::vec3& _position);

    void setScale(const ::glm::vec3& _scale);

    const ::glm::mat4 getFullTransform() const;

    inline const MeshList& getAttachedMeshes() const;

private:

    SceneNode(SceneManager* const _sceneManager);

    SceneNode(SceneManager* const _sceneManager, SceneNode* const _parent, const std::string& _name);

    SceneNode(SceneManager* const _sceneManager, const std::string& _name);

    ~SceneNode();

    void setNeedUpdate();

    SceneManager* const m_sceneManager;

    const bool m_isRootSCeneNode;

    SceneNode* m_parent { nullptr };

    // Stores Euler orientation in radian.
    ::glm::vec3 m_orientation { 0.f };

    ::glm::vec3 m_positon { 0.f };

    ::glm::vec3 m_scale { 1.f };

    mutable ::glm::mat4 m_fullTransform { 1.f };

    mutable bool m_needUpdate { false };

    SceneNodeList m_children {};

    MeshList m_attachedMeshes {};

};

inline const SceneNode::SceneNodeList& SceneNode::getChildren() const
{
    return m_children;
}

inline ::glm::vec3 SceneNode::getOrientation() const
{
    return ::glm::degrees(m_orientation);
}

inline const SceneNode::MeshList& SceneNode::getAttachedMeshes() const
{
    return m_attachedMeshes;
}

}
