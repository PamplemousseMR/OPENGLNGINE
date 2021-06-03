#include "OpenGLNgine/Render/Viewport.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/RenderWindow.hpp"

namespace Render
{

void Viewport::setViewport(float _x, float _y, float _width, float _height)
{
    GLNGINE_ASSERT_IF(_width < 0 || _height < 0 || _width > 1 || _height > 1, "The size of the viewport must fit in the range [0-1]");
    m_viewport = {_x, _y, _width, _height};
}

Viewport::Viewport(RenderWindow* const _renderWindow, Camera* const _camera, const std::string& _name):
    IResource(_name),
    m_renderWindow(_renderWindow),
    m_camera(_camera)
{
    GLNGINE_ASSERT_IF(!_renderWindow, "The render window mustn't be null");
    GLNGINE_ASSERT_IF(!_camera, "The camera mustn't be null");
    m_viewport = {0.f, 0.f, 1.f, 1.f};
    m_camera->_notifyViewportCreated(this);
}

Viewport::~Viewport()
{
    m_camera->_notifyViewportDestroyed(this);
}

}
