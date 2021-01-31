#include "OpenGLNgine/Render/RenderWindow.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/Render.hpp"

namespace Render
{

void RenderWindow::swapBuffers()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void RenderWindow::addListener(RenderWindowListener* const _listener)
{
    GLNGINE_ASSERT_IF(!_listener, "The listener mustn't be null");
    m_listeners.push_back(_listener);
}

Viewport* RenderWindow::addViewport(const std::string& _name, Camera* const _camera)
{
    if(m_viewports.find(_name) != m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _name + "' already exists");
    }

    Viewport* viewport = new Viewport(this, _camera, _name);
    m_viewports.emplace(_name, viewport);
    return viewport;
}

void RenderWindow::removeViewport(const Viewport* const _viewport)
{
    GLNGINE_ASSERT_IF(!_viewport, "The viewport mustn't be null");

    ViewportList::const_iterator it = m_viewports.find(_viewport->getName());
    if(it == m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _viewport->getName() + "' doesn't exists");
    }

    m_viewports.erase(it);
    delete _viewport;
}

void RenderWindow::removeAllViewports()
{
    ViewportList::iterator it = m_viewports.begin();
    while(it != m_viewports.end())
    {
        this->removeViewport(it->second);
        it = m_viewports.begin();
    }
}

Viewport* RenderWindow::getViewport(const std::string& _name) const
{
    if(m_viewports.find(_name) == m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _name + "' doesn't exists");
    }
    return m_viewports.at(_name);
}

RenderWindow::Initializer::Initializer()
{
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        GLNGINE_EXCEPTION("Can't initialize the render");
    }
}

void sizeCallback(GLFWwindow* _window, int _width, int _height)
{
    Render& render = Render::getInstance();

    for(const auto& rw : render.getRenderWindows())
    {
        if(rw.second->m_window == _window)
        {
            rw.second->m_height = _height;
            rw.second->m_width = _width;
            for(RenderWindowListener* const listener : rw.second->m_listeners)
            {
                listener->sizeModified(rw.second, _width, _height);
            }
            break;
        }
    }
}

void keyCallback(GLFWwindow* _window, int _key, int, int _action, int)
{
    Render& render = Render::getInstance();

    for(const auto& rw : render.getRenderWindows())
    {
        if(rw.second->m_window == _window)
        {
            RenderWindowListener::RENDERWINDOWLISTENER_KEY key = static_cast< RenderWindowListener::RENDERWINDOWLISTENER_KEY >(_key);
            for(RenderWindowListener* const listener : rw.second->m_listeners)
            {
                if(_action == GLFW_PRESS)
                {
                    listener->keyPressed(rw.second, key);
                }
                else if(_action == GLFW_REPEAT)
                {
                    listener->keyRepeated(rw.second, key);
                }
                else if(_action == GLFW_RELEASE)
                {
                    listener->keyRepeated(rw.second, key);
                }
                else
                {
                    GLNGINE_ASSERT("Unknown action");
                }
            }
            break;
        }
    }
}

RenderWindow::RenderWindow(Render* const _render, const std::string& _name, int _width, int _height) :
    IResource(_name),
    m_render(_render),
    m_width(_width),
    m_height(_height)
{
    GLNGINE_ASSERT_IF(!_render, "The render mustn't be null");
    m_window = glfwCreateWindow(_width, _height, m_name.c_str(), m_monitor, nullptr);
    if(!m_window)
    {
        GLNGINE_EXCEPTION("Can't create the render window");
    }

    this->makeCurrent();
    const static Initializer s_INITIALIZER;

    glfwSetWindowSizeCallback(m_window, sizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);
}

RenderWindow::~RenderWindow()
{
    this->removeAllViewports();
    glfwDestroyWindow(m_window);
}

}
