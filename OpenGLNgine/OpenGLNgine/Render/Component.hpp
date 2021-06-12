#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

namespace Render
{

class SceneManager;

class Component : public ::Core::IResource
{

    friend SceneManager;

public:

    Component(const Component&) = delete;

    Component(Component&&) = delete;

    Component& operator=(const Component&) = delete;

    Component& operator=(Component&&) = delete;

    inline SceneManager* getSceneManager() const;

protected:

    Component(SceneManager* const _sceneManager, const std::string& _name);

    ~Component();

    SceneManager* const m_sceneManager;

};

inline SceneManager* Component::getSceneManager() const
{
    return m_sceneManager;
}

}
