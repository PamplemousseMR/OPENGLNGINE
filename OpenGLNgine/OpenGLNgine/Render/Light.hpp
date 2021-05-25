#pragma once

#include "OpenGLNgine/Render/Component.hpp"

#include <glm/glm.hpp>

namespace Render
{

/// Manages the light type.
enum LIGHT_TYPE
{
    LT_POINT,
    LT_DIRECTIONAL
};

class Light final : public Component
{

    friend SceneManager;

public:

    Light(const Light&) = delete;

    Light(Light&&) = delete;

    Light& operator=(const Light&) = delete;

    Light& operator=(Light&&) = delete;

    inline void setAmbient(const ::glm::vec3& _ambient);

    inline const ::glm::vec3& getAmbient() const;

    inline void setDiffuse(const ::glm::vec3& _diffuse);

    inline const ::glm::vec3& getDiffuse() const;

    inline void setSpecular(const ::glm::vec3& _specular);

    inline const ::glm::vec3& getSpecular() const;

    inline void setType(LIGHT_TYPE _type);

    inline LIGHT_TYPE getType();

    inline void setPosition(const ::glm::vec3& _position);

    inline const ::glm::vec3& getPosition() const;

    inline void setDirection(const ::glm::vec3& _direction);

    inline const ::glm::vec3& getDirection() const;

    ::glm::vec4 getShaderPosition() const;

private:

    Light(SceneManager* const _sceneManager, const std::string& _name);

    ~Light();

    ::glm::vec3 m_ambient { 1.f, 1.f, 1.f };

    ::glm::vec3 m_diffuse { 1.f, 1.f, 1.f };

    ::glm::vec3 m_specular { 1.f, 1.f, 1.f };

    LIGHT_TYPE m_type { LT_POINT };

    ::glm::vec3 m_position { 0.f, 0.f, 0.f};

    ::glm::vec3 m_direction { 0.f, 0.f, -1.f};

};

inline void Light::setAmbient(const ::glm::vec3& _ambient)
{
    m_ambient = _ambient;
}

inline const ::glm::vec3& Light::getAmbient() const
{
    return m_ambient;
}

inline void Light::setDiffuse(const ::glm::vec3& _diffuse)
{
    m_diffuse = _diffuse;
}

inline const ::glm::vec3& Light::getDiffuse() const
{
    return m_diffuse;
}

inline void Light::setSpecular(const ::glm::vec3& _specular)
{
    m_specular = _specular;
}

inline const ::glm::vec3& Light::getSpecular() const
{
    return m_specular;
}

inline void Light::setType(LIGHT_TYPE _type)
{
    m_type = _type;
}

inline LIGHT_TYPE Light::getType()
{
    return m_type;
}

inline void Light::setPosition(const ::glm::vec3& _position)
{
   m_position = _position;
}

inline const ::glm::vec3& Light::getPosition() const
{
    return m_position;
}

inline void Light::setDirection(const ::glm::vec3& _direction)
{
    m_direction = _direction;
}

inline const ::glm::vec3& Light::getDirection() const
{
    return m_direction;
}

}
