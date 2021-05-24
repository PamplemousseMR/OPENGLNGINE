#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Render/Component.hpp"

#include <glm/glm.hpp>

#include <map>
#include <string>

namespace Render
{

class SceneManager;

class SceneNode final : public Core::IResource
{

    friend SceneManager;

public:

    typedef std::map< std::string, SceneNode* > SceneNodeList;

    SceneNode(const SceneNode&) = delete;

    SceneNode(SceneNode&&) = delete;

    SceneNode& operator=(const SceneNode&) = delete;

    SceneNode& operator=(SceneNode&&) = delete;

    SceneNode* createChild(const std::string& _name);

    inline const SceneNodeList& getChildren() const;

    void removeAndDestroyChild(SceneNode* const _child);

    void removeAndDestroyAllChildren();

    void attach(Component* const _component);

    void dettach(Component* const _component);

    void dettachAll();

    void setPosition(const glm::vec3 _position);

    inline const glm::vec3& getPosition() const;

    void setScale(const glm::vec3 _scale);

    const glm::mat4 getFullTransform() const;

private:

    typedef std::map< std::string, Component* > ComponentList;

    SceneNode(SceneManager* const _sceneManager);

    SceneNode(SceneManager* const _sceneManager, SceneNode* const _parent, const std::string& _name);

    SceneNode(SceneManager* const _sceneManager, const std::string& _name);

    ~SceneNode();

    void setNeedUpdate();

    SceneManager* const m_sceneManager;

    const bool m_isRootSCeneNode;

    SceneNode* m_parent { nullptr };

    glm::vec3 m_positon { 0.f };

    glm::vec3 m_scale { 1.f };

    mutable glm::mat4 m_fullTransform { 1.f };

    mutable bool m_needUpdate { false };

    SceneNodeList m_children {};

    ComponentList m_attachedComponents {};

};

inline const SceneNode::SceneNodeList& SceneNode::getChildren() const
{
    return m_children;
}

inline const glm::vec3& SceneNode::getPosition() const
{
    return m_positon;
}

}
