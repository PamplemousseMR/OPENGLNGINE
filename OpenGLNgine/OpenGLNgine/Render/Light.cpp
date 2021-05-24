#include "OpenGLNgine/Render/Light.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace Render
{

::glm::vec4 Light::getShaderPosition() const
{
    switch (m_type) {
    case LT_POINT:
        return ::glm::vec4(m_position, 1.f);
        break;
    case LT_DIRECTIONAL:
        ::glm::vec4 direction(-m_direction, 0.f);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle light type");
    }
}

}
