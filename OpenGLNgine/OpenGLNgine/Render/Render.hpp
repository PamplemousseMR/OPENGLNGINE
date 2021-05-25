#pragma once

#include "OpenGLNgine/Render/RenderWindow.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

#include <map>
#include <string>

namespace Render
{

/**
 * @brief This singleton is the starting point of the whole renderer.
 */
class Render final
{

    friend RenderWindow;
    friend SceneManager;

public:

    typedef std::map< std::string, RenderWindow* > RenderWindowList;

    typedef std::map< std::string, SceneManager* > SceneManagerList;

    /**
     * @brief Gets the only instance of this class.
     * @return The only Render instance.
     */
    static Render& getInstance();

    /// Deleted copy constructor.
    Render(const Render&) = delete;

    /// Deleted move constructor.
    Render(Render&&) = delete;

    /// Deleted copy operator.
    Render& operator=(const Render&) = delete;

    /// Deleted move operator.
    Render& operator=(Render&&) = delete;

    /**
     * @brief Creates a render window.
     * @param _name The name of the window.
     * @param _width The width of the window.
     * @param _height The height of the window.
     * @return The render window.
     */
    RenderWindow* createRenderWindow(const std::string& _name, int _width, int _height);

    /**
     * @brief Destroys a render window.
     * @param _renderWindow The render window to destroy.
     */
    Render::RenderWindowList::iterator destroyRenderWindow(const RenderWindow* const _renderWindow);

    /// Destroys all render window.
    void destroyAllRenderWindow();

    /**
     * @brief Gets all render window.
     * @return All render window.
     */
    inline const RenderWindowList& getRenderWindows() const;

    /**
     * @brief Creates a scene manager.
     * @param _name The name of the scene manager.
     * @return The scene manager.
     */
    SceneManager* createSceneManager(const std::string& _name);

    /**
     * @brief Destroys a scene manager.
     * @param _sceneManager The scene manager to destroy.
     */
    void destroySceneManager(const SceneManager* const _sceneManager);

    /// Destroys all scene manager.
    void destroyAllSceneManagers();

    /**
     * @brief Gets all scene manager.
     * @return All scene manager.
     */
    inline const SceneManagerList& getSceneManagers() const;

private:

    /**
     * @brief This struct allows to initialize the render one time.
     */
    struct Initializer final
    {
        /// Initializes the render.
        Initializer();

        /// Terminates the render.
        ~Initializer();
    };

    /// Contains the only instance of this class.
    static Render* s_instance;

    /// Creates and initializes the render.
    Render();

    /// Destroys and terminates the render.
    ~Render();

    /// Stores all render window.
    RenderWindowList m_renderWindows {};

    /// Stores all scene manager.
    SceneManagerList m_sceneManagers {};

};

inline const Render::RenderWindowList& Render::getRenderWindows() const
{
    return m_renderWindows;
}

inline const Render::SceneManagerList& Render::getSceneManagers() const
{
    return m_sceneManagers;
}

}
