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

    void setProjection(float _fovy, float _aspect, float _near, float _far);

    inline const ::glm::mat4 getProjection() const;

    void lookAt(const ::glm::vec3& _target);

    void setPosition(const ::glm::vec3& _position);

    inline const ::glm::mat4 getView() const;

    inline float getFovy() const;

    inline float getAspect() const;

    inline float getNear() const;

    inline float getFar() const;

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

    ::glm::mat4 m_projection { 1.f };

    ::glm::mat4 m_view { 1.f };

    ::glm::vec3 m_lookAt { 0.f };

    ::glm::vec3 m_position { 0.f };

    float m_fovy { 0.f };

    float m_aspect { 0.f };

    float m_near { 0.f };

    float m_far { 0.f };

};

inline const ::glm::mat4 Camera::getProjection() const
{
    return m_projection;
}

inline const ::glm::mat4 Camera::getView() const
{
    return m_view;
}

inline float Camera::getFovy() const
{
    return m_fovy;
}

inline float Camera::getAspect() const
{
    return m_aspect;
}

inline float Camera::getNear() const
{
    return m_near;
}

inline float Camera::getFar() const
{
    return m_far;
}

}
