#include "OpenGLNgine/Render/Render.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <GLFW/glfw3.h>

namespace  Render
{

Render Render::s_instance {};

Render& Render::getInstance()
{
    return s_instance;
}

RenderWindow* Render::createRenderWindow(const std::string& _name, int _width, int _height, int _sample)
{
    if(m_renderWindows.find(_name) != m_renderWindows.end())
    {
        GLNGINE_EXCEPTION("A render window with the name '" + _name + "' already exists");
    }

    auto rw = new RenderWindow(_name, _width, _height, _sample);
    m_renderWindows.emplace(_name, rw);
    return rw;
}

Render::RenderWindowList::iterator Render::destroyRenderWindow(const RenderWindow* const _renderWindow)
{
    GLNGINE_ASSERT_IF(!_renderWindow, "The render window shall not be null");

    const RenderWindowList::const_iterator it = m_renderWindows.find(_renderWindow->getName());
    if(it == m_renderWindows.end())
    {
        GLNGINE_EXCEPTION("A render window with the name '" + _renderWindow->getName() + "' doesn't exists");
    }

    const Render::RenderWindowList::iterator eraseIt = m_renderWindows.erase(it);
    delete _renderWindow;
    return eraseIt;
}

void Render::destroyAllRenderWindow()
{
    RenderWindowList::iterator it = m_renderWindows.begin();
    while(it != m_renderWindows.end())
    {
        this->destroyRenderWindow(it->second);
        it = m_renderWindows.begin();
    }
}

Render::Render()
{
    if(!glfwInit())
    {
        GLNGINE_EXCEPTION("Can't initialize the render");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

Render::~Render()
{
    this->destroyAllRenderWindow();
    glfwTerminate();
}

}
