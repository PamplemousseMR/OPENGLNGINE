#pragma once

#include "OpenGLNgine/Render/Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>

namespace Render
{

class Viewport;

class Camera final : public Component
{

    friend SceneManager;
    friend Viewport;

public:

    inline void setProjection(float _fovy, float _aspect, float _near, float _far);

    inline const glm::mat4 getProjection() const;

    void lookAt(const glm::vec3& _target);

    void setPosition(const glm::vec3& _position);

    inline const glm::mat4 getView() const;

private:

    typedef std::map< std::string, Viewport* > ViewportList;

    Camera(SceneManager* const _sceneManager, const std::string& _name);

    Camera(const Camera&) = delete;

    Camera(Camera&&) = delete;

    Camera& operator=(const Camera&) = delete;

    Camera& operator=(Camera&&) = delete;

    ~Camera();

    void notifyViewportCreated(Viewport* const _viewport);

    void notifyViewportDestroyed(Viewport* const _viewport);

    ViewportList m_viewports {};

    glm::mat4 m_projection { 1.f };

    glm::mat4 m_view { 1.f };

    glm::vec3 m_lookAt { 0.f };

    glm::vec3 m_position { 0.f };

};

inline void Camera::setProjection(float _fovy, float _aspect, float _near, float _far)
{
    m_projection = glm::perspective(_fovy, _aspect, _near, _far);
}

inline const glm::mat4 Camera::getProjection() const
{
    return m_projection;
}

inline const glm::mat4 Camera::getView() const
{
    return m_view;
}

}
