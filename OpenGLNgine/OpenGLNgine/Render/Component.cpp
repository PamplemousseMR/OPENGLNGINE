#include "OpenGLNgine/Render/Component.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

Component::Component(SceneManager* const _sceneManager, const std::string& _name):
    IResource(_name),
    m_sceneManager(_sceneManager)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager mustn't be null");
}

Component::~Component()
{
    if(isAttached())
    {
        m_parent->dettach(this);
    }
}

}
