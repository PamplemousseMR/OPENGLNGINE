#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include "OpenGLNgine/GL/DrawCall.hpp"
#include "OpenGLNgine/GL/PixelOperation.hpp"
#include "OpenGLNgine/GL/Rasterizer.hpp"

#include "OpenGLNgine/Render/Camera.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"
#include "OpenGLNgine/Render/SceneNode.hpp"
#include "OpenGLNgine/Render/Mesh.hpp"
#include "OpenGLNgine/Render/Viewport.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <set>
#include <string>
#include <vector>

namespace Render
{

class Render;

/**
 * @brief This listener gets callbacks on RenderWindow.
 */
class RenderWindowListener
{

public:

    /// Manages keyboard keys.
    enum RENDERWINDOWLISTENER_KEY : int
    {
        RK_SPACE = GLFW_KEY_SPACE,
        RK_APOSTROPHE = GLFW_KEY_APOSTROPHE,
        RK_COMMA = GLFW_KEY_COMMA,
        RK_MINUS = GLFW_KEY_MINUS,
        RK_PERIOD = GLFW_KEY_PERIOD,
        RK_SLASH = GLFW_KEY_SLASH,
        RK_0 = GLFW_KEY_0,
        RK_1 = GLFW_KEY_1,
        RK_2 = GLFW_KEY_2,
        RK_3 = GLFW_KEY_3,
        RK_4 = GLFW_KEY_4,
        RK_5 = GLFW_KEY_5,
        RK_6 = GLFW_KEY_6,
        RK_7 = GLFW_KEY_7,
        RK_8 = GLFW_KEY_8,
        RK_9 = GLFW_KEY_9,
        RK_SEMICOLON = GLFW_KEY_SEMICOLON,
        RK_EQUAL = GLFW_KEY_EQUAL,
        RK_A = GLFW_KEY_A,
        RK_B = GLFW_KEY_B,
        RK_C = GLFW_KEY_C,
        RK_D = GLFW_KEY_D,
        RK_E = GLFW_KEY_E,
        RK_F = GLFW_KEY_F,
        RK_G = GLFW_KEY_G,
        RK_H = GLFW_KEY_H,
        RK_I = GLFW_KEY_I,
        RK_J = GLFW_KEY_J,
        RK_K = GLFW_KEY_K,
        RK_L = GLFW_KEY_L,
        RK_M = GLFW_KEY_M,
        RK_N = GLFW_KEY_N,
        RK_O = GLFW_KEY_O,
        RK_P = GLFW_KEY_P,
        RK_Q = GLFW_KEY_Q,
        RK_R = GLFW_KEY_R,
        RK_S = GLFW_KEY_S,
        RK_T = GLFW_KEY_T,
        RK_U = GLFW_KEY_U,
        RK_V = GLFW_KEY_V,
        RK_W = GLFW_KEY_W,
        RK_X = GLFW_KEY_X,
        RK_Y = GLFW_KEY_Y,
        RK_Z = GLFW_KEY_Z,
        RK_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
        RK_BACKSLASH = GLFW_KEY_BACKSLASH,
        RK_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
        RK_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
        RK_WORLD_1 = GLFW_KEY_WORLD_1,
        RK_WORLD_2 = GLFW_KEY_WORLD_2,
        RK_ESCAPE = GLFW_KEY_ESCAPE,
        RK_ENTER = GLFW_KEY_ENTER,
        RK_TAB = GLFW_KEY_TAB,
        RK_BACKSPACE = GLFW_KEY_BACKSPACE,
        RK_INSERT = GLFW_KEY_INSERT,
        RK_DELETE = GLFW_KEY_DELETE,
        RK_RIGHT = GLFW_KEY_RIGHT,
        RK_LEFT = GLFW_KEY_LEFT,
        RK_DOWN = GLFW_KEY_DOWN,
        RK_UP = GLFW_KEY_UP,
        RK_PAGE_UP = GLFW_KEY_PAGE_UP,
        RK_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
        RK_HOME = GLFW_KEY_HOME,
        RK_END = GLFW_KEY_END,
        RK_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        RK_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
        RK_NUM_LOCK = GLFW_KEY_NUM_LOCK,
        RK_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
        RK_PAUSE = GLFW_KEY_PAUSE,
        RK_F1 = GLFW_KEY_F1,
        RK_F2 = GLFW_KEY_F2,
        RK_F3 = GLFW_KEY_F3,
        RK_F4 = GLFW_KEY_F4,
        RK_F5 = GLFW_KEY_F5,
        RK_F6 = GLFW_KEY_F6,
        RK_F7 = GLFW_KEY_F7,
        RK_F8 = GLFW_KEY_F8,
        RK_F9 = GLFW_KEY_F9,
        RK_F10 = GLFW_KEY_F10,
        RK_F11 = GLFW_KEY_F11,
        RK_F12 = GLFW_KEY_F12,
        RK_F13 = GLFW_KEY_F13,
        RK_F14 = GLFW_KEY_F14,
        RK_F15 = GLFW_KEY_F15,
        RK_F16 = GLFW_KEY_F16,
        RK_F17 = GLFW_KEY_F17,
        RK_F18 = GLFW_KEY_F18,
        RK_F19 = GLFW_KEY_F19,
        RK_F20 = GLFW_KEY_F20,
        RK_F21 = GLFW_KEY_F21,
        RK_F22 = GLFW_KEY_F22,
        RK_F23 = GLFW_KEY_F23,
        RK_F24 = GLFW_KEY_F24,
        RK_F25 = GLFW_KEY_F25,
        RK_KP_0 = GLFW_KEY_KP_0,
        RK_KP_1 = GLFW_KEY_KP_1,
        RK_KP_2 = GLFW_KEY_KP_2,
        RK_KP_3 = GLFW_KEY_KP_3,
        RK_KP_4 = GLFW_KEY_KP_4,
        RK_KP_5 = GLFW_KEY_KP_5,
        RK_KP_6 = GLFW_KEY_KP_6,
        RK_KP_7 = GLFW_KEY_KP_7,
        RK_KP_8 = GLFW_KEY_KP_8,
        RK_KP_9 = GLFW_KEY_KP_9,
        RK_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
        RK_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
        RK_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
        RK_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
        RK_KP_ADD = GLFW_KEY_KP_ADD,
        RK_KP_ENTER = GLFW_KEY_KP_ENTER,
        RK_KP_EQUAL = GLFW_KEY_KP_EQUAL,
        RK_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        RK_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
        RK_LEFT_ALT = GLFW_KEY_LEFT_ALT,
        RK_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
        RK_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
        RK_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
        RK_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
        RK_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
        RK_MENU = GLFW_KEY_MENU
    };

    /**
     * @brief Called when window is resized.
     * @param _rw The resized render window.
     * @param _width The new width of the render window.
     * @param _height The new height of the render window.
     */
    virtual void sizeModified([[maybe_unused]] RenderWindow* const _rw, [[maybe_unused]] int _width, [[maybe_unused]] int _height) {}

    /**
     * @brief Called when a keyboard key is pressed.
     * @param _rw The render window.
     * @param _key The pressed key.
     */
    virtual void keyPressed([[maybe_unused]] RenderWindow* const _rw, [[maybe_unused]] RENDERWINDOWLISTENER_KEY _key) {}

    /**
     * @brief Called when a keyboard key is repeated.
     * @param _rw The render window.
     * @param _key The repeated key.
     */
    virtual void keyRepeated([[maybe_unused]] RenderWindow* const _rw, [[maybe_unused]] RENDERWINDOWLISTENER_KEY _key) {}

    /**
     * @brief Called when a keyboard key is released.
     * @param _rw The render window.
     * @param _key The released key.
     */
    virtual void keyRelease([[maybe_unused]] RenderWindow* const _rw, [[maybe_unused]] RENDERWINDOWLISTENER_KEY _key) {}

};

/**
 * @brief Manages a target window.
 */
class RenderWindow final : public ::Core::IResource
{

    friend Render;

public:

    typedef std::map< std::string, SceneManager* > SceneManagerList;

    typedef std::map< std::string, Viewport* > ViewportList;

    /// Deleted copy constructor.
    RenderWindow(const RenderWindow&) = delete;

    /// Deleted move constructor.
    RenderWindow(RenderWindow&&) = delete;

    /// Deleted copy operator.
    RenderWindow& operator=(const RenderWindow&) = delete;

    /// Deleted move operator.
    RenderWindow& operator=(RenderWindow&&) = delete;

    /**
     * @brief Sets the number of samples of the default frame buffer.
     * @param _samples The number of samples.
     */
    inline void setSamples(int _samples) const;

    /// Makes the render window GL context as current.
    inline void makeCurrent() const;

    /// render in the render window.
    void render() const;

    /// Swaps the front and back buffers.
    void swapBuffers();

    /// Sets the close flag to the window.
    inline void shouldBeClose(bool _close);

    /**
     * @brief Checks the close flag on the window.
     * @return True if the window should be closed.
     */
    inline bool shouldBeClose();

    /**
     * @brief Get the window width.
     * @return The window width.
     */
    inline int getWidth() const;

    /**
     * @brief Get the window height.
     * @return The window height.
     */
    inline int getHeight() const;

    /**
     * @brief Adds a listener to the render window.
     * @param _listener The listener to add to the window.
     */
    void addListener(RenderWindowListener* const _listener);

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

    /**
     * @brief Adds a new rendering viewport from a camera
     * @param _name The name of the viewport.
     * @param _camera The camera used to render in the viewport.
     * @return The created viewport.
     */
    Viewport* addViewport(const std::string& _name, Camera* const _camera);

    /**
     * @brief Removes the given viewport.
     * @param _viewport The viewpor to removed.
     */
    void removeViewport(const Viewport* const _viewport);

    /// Removes all viewports.
    void removeAllViewports();

    /**
     * @brief Gets all viewports
     * @return All viewports.
     */
    inline const ViewportList& getViewports() const;

    /**
     * @brief Get a specific viewport.
     * @param _name The name of the viewport to retrieve.
     * @return The viewport.
     */
    Viewport* getViewport(const std::string& _name) const;

private:

    typedef std::vector< RenderWindowListener* > RenderWindowListeners;

    /**
     * @brief This struct allows to initialize the render window one time.
     */
    struct Initializer final
    {
        /// Initializes the render window.
        Initializer();
    };

    /**
     * @brief Called when the render window is resized.
     * @param _window Resized window.
     * @param _width New width of the window.
     * @param _height New height of the window.
     */
    friend void sizeCallback(GLFWwindow* _window, int _width, int _height);

    /**
     * @brief Called when a key is pressed, repeated or released.
     * @param _window Related window.
     * @param _key The key.
     * @param _action The action.
     */
    friend void keyCallback(GLFWwindow* _window, int _key, int, int _action, int);

    /**
     * @brief Creates a render window.
     * @param _name The name of the window.
     * @param _width The width of the window.
     * @param _height The height of the window.
     */
    RenderWindow(const std::string& _name, int _width, int _height);

    /// Destroys the render window.
    ~RenderWindow();

    /// Stores all listener.
    RenderWindowListeners m_listeners {};

    /// Contains the monitor to use for full screen mode
    GLFWmonitor* m_monitor { nullptr };

    /// Containms the the render window.
    GLFWwindow* m_window { nullptr };

    /// Defines the width of the window.
    int m_width { 0 };

    /// Defines the height of the window.
    int m_height { 0 };

    /// Stores all scene manager.
    SceneManagerList m_sceneManagers {};

    /// Stores all viewport.
    ViewportList m_viewports {};

};

inline void RenderWindow::setSamples(int _samples) const
{
    glfwWindowHint(GLFW_SAMPLES, _samples);
}

inline void RenderWindow::makeCurrent() const
{
    glfwMakeContextCurrent(m_window);
}

inline void RenderWindow::shouldBeClose(bool _close)
{
    glfwSetWindowShouldClose(m_window, _close);
}

inline bool RenderWindow::shouldBeClose()
{
    return glfwWindowShouldClose(m_window);
}

inline int RenderWindow::getWidth() const
{
    return m_width;
}

inline int RenderWindow::getHeight() const
{
    return m_height;
}

inline const RenderWindow::SceneManagerList& RenderWindow::getSceneManagers() const
{
    return m_sceneManagers;
}

inline const RenderWindow::ViewportList& RenderWindow::getViewports() const
{
    return m_viewports;
}

}
