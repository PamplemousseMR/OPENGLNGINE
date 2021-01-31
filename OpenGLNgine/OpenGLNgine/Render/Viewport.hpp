#pragma once

#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Render/Camera.hpp"

#include <array>
#include <string>

namespace Render
{

class RenderWindow;

/**
 * @brief Manages a viewport attached to a render window.
 */
class Viewport final : public Core::IResource
{

    friend RenderWindow;

public:

    /**
     * @brief Gets the camera attached to this viewport.
     * @return The attached camera.
     */
    inline Camera* getCamera() const;

    /**
     * @brief Sets the size and the position of the viewport.
     * @param _x Position in pixel of the x coordinate.
     * @param _y Position in pixel of the y coordinate.
     * @param _width Width of the viewport in pixel.
     * @param _height Height of the viewport in pixel.
     */
    void setViewport(int _x, int _y, int _width, int _height);

    /**
     * @brief Gets the viewport size and position
     * @return The position and the size.
     */
    inline const std::array< int, 4 >& getViewport() const;

    /**
     * @brief Sets the background color of the viewport.
     * @param _r Red channel normalised values.
     * @param _g Geen channel normalised values.
     * @param _b Blue channel normalised values.
     * @param _a Alpha channel normalised values.
     */
    inline void setClearColor(float _r, float _g, float _b, float _a);

    /**
     * @brief Gets the background color of the viewport.
     * @return The background color.
     */
    inline const std::array< float, 4 >& getClearColor() const;

    /**
     * @brief Gets the render window where the viewport is attached.
     * @return The related render window.
     */
    inline RenderWindow* getRenderWindow() const;

private:

    /**
     * @brief Creates a new viewport attached to a render window.
     * @param _renderWindow The related render window.
     * @param _camera The camera atached to this viewport.
     * @param _name The name of the viewport.
     */
    Viewport(RenderWindow* const _renderWindow, Camera* const _camera, const std::string& _name);

    /// Deleted copy constructor.
    Viewport(const Viewport&) = delete;

    /// Deleted move constructor.
    Viewport(Viewport&&) = delete;

    /// Deleted copy operator.
    Viewport& operator=(const Viewport&) = delete;

    /// Deleted move operator.
    Viewport& operator=(Viewport&&) = delete;

    /// Destroys the viewport and notifies the attached camera.
    ~Viewport();

    /// Stores the related render window.
    RenderWindow* const m_renderWindow;

    /// Defines the position and the size of the viewport.
    std::array< int, 4 > m_viewport { 0, 0, 1, 1 };

    /// Defines the background color.
    std::array< float, 4 > m_clearColor { 0.f, 0.f, 0.f, 0.f };

    /// Attached camera.
    Camera* const m_camera;

};

inline Camera *Viewport::getCamera() const
{
    return m_camera;
}

inline const std::array<int, 4>& Viewport::getViewport() const
{
    return m_viewport;
}
inline void Viewport::setClearColor(float _r, float _g, float _b, float _a)
{
    m_clearColor = {_r, _g, _b, _a};
}

inline const std::array< float, 4 >& Viewport::getClearColor() const
{
    return m_clearColor;
}

inline RenderWindow* Viewport::getRenderWindow() const
{
    return m_renderWindow;
}

}
