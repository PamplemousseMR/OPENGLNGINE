#include "OpenGLNgine/Render/Camera.hpp"
#include "OpenGLNgine/Render/Render.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <GLFW/glfw3.h>

namespace  Render
{

Render* Render::s_instance = nullptr;

Render& Render::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

RenderWindow* Render::createRenderWindow(const std::string& _name, int _width, int _height)
{
    if(m_renderWindows.find(_name) != m_renderWindows.end())
    {
        GLNGINE_EXCEPTION("A render window with the name '" + _name + "' already exists");
    }

    auto rw = new RenderWindow(this, _name, _width, _height);
    m_renderWindows.emplace(_name, rw);
    return rw;
}

void Render::destroyRenderWindow(const RenderWindow* const _renderWindow)
{
    GLNGINE_ASSERT_IF(!_renderWindow, "The render window mustn't be null");

    RenderWindowList::const_iterator it = m_renderWindows.find(_renderWindow->getName());
    if(it == m_renderWindows.end())
    {
        GLNGINE_EXCEPTION("A render window with the name '" + _renderWindow->getName() + "' doesn't exists");
    }

    m_renderWindows.erase(it);
    delete _renderWindow;
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

Camera* Render::createCamera(const std::string& _name)
{
    if(m_cameras.find(_name) != m_cameras.end())
    {
        GLNGINE_EXCEPTION("A camera with the name '" + _name + "' already exists");
    }

    auto cam = new Camera(this, _name);
    m_cameras.emplace(_name, cam);
    return cam;
}

void Render::destroyCamera(const Camera* const _camera)
{
    GLNGINE_ASSERT_IF(!_camera, "The camera mustn't be null");

    CameraList::const_iterator it = m_cameras.find(_camera->getName());
    if(it == m_cameras.end())
    {
        GLNGINE_EXCEPTION("A camera with the name '" + _camera->getName() + "' doesn't exists");
    }

    m_cameras.erase(it);
    delete _camera;
}

void Render::destroyAllCamera()
{
    CameraList::iterator it = m_cameras.begin();
    while(it != m_cameras.end())
    {
        this->destroyCamera(it->second);
        it = m_cameras.begin();
    }
}

Render::Initializer::Initializer()
{
    Render::s_instance = new Render();
}

Render::Initializer::~Initializer()
{
    delete Render::s_instance;
    Render::s_instance = nullptr;
}

Render::Render()
{
    if(!glfwInit())
    {
        GLNGINE_EXCEPTION("Can't initialize the render");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
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
