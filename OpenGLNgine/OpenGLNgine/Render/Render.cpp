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

    auto rw = new RenderWindow(_name, _width, _height);
    m_renderWindows.emplace(_name, rw);
    return rw;
}

Render::RenderWindowList::iterator Render::destroyRenderWindow(const RenderWindow* const _renderWindow)
{
    GLNGINE_ASSERT_IF(!_renderWindow, "The render window mustn't be null");

    RenderWindowList::const_iterator it = m_renderWindows.find(_renderWindow->getName());
    if(it == m_renderWindows.end())
    {
        GLNGINE_EXCEPTION("A render window with the name '" + _renderWindow->getName() + "' doesn't exists");
    }

    Render::RenderWindowList::iterator eraseIt = m_renderWindows.erase(it);
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

SceneManager* Render::createSceneManager(const std::string& _name)
{
    if(m_sceneManagers.find(_name) != m_sceneManagers.end())
    {
        GLNGINE_EXCEPTION("A scene manager with the name '" + _name + "' already exists");
    }

    auto sm = new SceneManager(_name);
    m_sceneManagers.emplace(_name, sm);
    return sm;
}

void Render::destroySceneManager(const SceneManager* const _sceneManager)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager mustn't be null");

    SceneManagerList::const_iterator it = m_sceneManagers.find(_sceneManager->getName());
    if(it == m_sceneManagers.end())
    {
        GLNGINE_EXCEPTION("A scene manager with the name '" + _sceneManager->getName() + "' doesn't exists");
    }

    m_sceneManagers.erase(it);
    delete _sceneManager;
}

void Render::destroyAllSceneManagers()
{
    SceneManagerList::iterator it = m_sceneManagers.begin();
    while(it != m_sceneManagers.end())
    {
        this->destroySceneManager(it->second);
        it = m_sceneManagers.begin();
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
    this->destroyAllSceneManagers();
    glfwTerminate();
}

}
