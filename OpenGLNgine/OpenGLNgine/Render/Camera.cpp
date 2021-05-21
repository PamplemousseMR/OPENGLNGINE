#include "OpenGLNgine/Render/Camera.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/RenderWindow.hpp"
#include "OpenGLNgine/Render/Viewport.hpp"

#include <glm/gtx/string_cast.hpp>

namespace Render
{

void Camera::setProjection(float _fovy, float _aspect, float _near, float _far)
{
    m_fovy = _fovy;
    m_aspect = _aspect;
    m_near = _near;
    m_far = _far;
    m_projection = glm::perspective(_fovy, _aspect, _near, _far);
}

void Camera::lookAt(const glm::vec3& _target)
{
    m_lookAt = _target;

    m_view = glm::lookAt(m_position, m_lookAt, glm::vec3(0,1,0));
}

void Camera::setPosition(const glm::vec3& _position)
{
   m_position = _position;

   m_view = glm::lookAt(m_position, m_lookAt, glm::vec3(0,1,0));
}

Camera::Camera(Render* _render, const std::string& _name):
    IResource(_name),
    m_render(_render)
{
}

Camera::~Camera()
{
    for(const auto& viewport : m_viewports)
    {
        viewport.second->getRenderWindow()->removeViewport(viewport.second);
    }
}

void Camera::notifyViewportCreated(Viewport* const _viewport)
{
    if(m_viewports.find(_viewport->getName()) != m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _viewport->getName() + "' already exists");
    }
    m_viewports.emplace(_viewport->getName(), _viewport);
}

void Camera::notifyViewportDestroyed(Viewport* const _viewport)
{
    ViewportList::const_iterator it = m_viewports.find(_viewport->getName());
    if(it == m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _viewport->getName() + "' doesn't exists");
    }
    m_viewports.erase(it);
}

}
