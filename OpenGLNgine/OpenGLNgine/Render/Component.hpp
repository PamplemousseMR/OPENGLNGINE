#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

namespace Render
{

class SceneManager;
class SceneNode;

class Component : public ::Core::IResource
{

    friend SceneManager;
    friend SceneNode;

public:

    Component(const Component&) = delete;

    Component(Component&&) = delete;

    Component& operator=(const Component&) = delete;

    Component& operator=(Component&&) = delete;

    inline SceneManager* getSceneManager() const;

    inline bool isAttached() const;

    inline SceneNode* getParent() const;

protected:

    Component(SceneManager* const _sceneManager, const std::string& _name);

    ~Component();

    inline void setParent(SceneNode* const _sceneNode);

    SceneManager* const m_sceneManager;

    SceneNode* m_parent { nullptr };

};

inline SceneManager* Component::getSceneManager() const
{
    return m_sceneManager;
}

inline bool Component::isAttached() const
{
    return m_parent != nullptr;
}

inline SceneNode* Component::getParent() const
{
    return m_parent;
}

inline void Component::setParent(SceneNode* const _sceneNode)
{
    m_parent = _sceneNode;
}

}
