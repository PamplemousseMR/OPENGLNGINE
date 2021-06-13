#include "OpenGLNgine/Render/Light.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

Light::Light(SceneManager* const _sceneManager, const std::string& _name):
    Component(_sceneManager, _name)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager shall not be null");
}

Light::~Light()
{
}

::glm::vec4 Light::getShaderPosition() const
{
    switch (m_type) {
    case LT_POINT:
        return ::glm::vec4(m_position, 1.f);
        break;
    case LT_DIRECTIONAL:
        return ::glm::vec4(-m_direction, 0.f);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle light type");
    }
}

}
