#pragma once

#include "Component.hpp"

#include <glm/common.hpp>

namespace Component
{

class Light : public Component
{

public:

    Light(const std::string&) noexcept;
    ~Light() noexcept;

    std::ostream& print(std::ostream&) const noexcept;

    inline const glm::vec3& getAmbient() const noexcept;
    inline const glm::vec3& getDiffuse() const noexcept;
    inline const glm::vec3& getSpecular() const noexcept;
    inline float getConstant() const noexcept;
    inline float getLinear() const noexcept;
    inline float getQuadratic() const noexcept;

    inline void setAmbient(const glm::vec3&) noexcept;
    inline void setDiffuse(const glm::vec3&) noexcept;
    inline void setSpecular(const glm::vec3&) noexcept;
    inline void setConstant(float) noexcept;
    inline void setLinear(float) noexcept;
    inline void setQuadratic(float) noexcept;

protected:

    glm::vec3 m_ambient {1, 1, 1};
    glm::vec3 m_diffuse {1, 1, 1};
    glm::vec3 m_specular {1, 1, 1};
    float m_constant {1.0};
    float m_linear {1.0};
    float m_quadratic {1.0};

};

std::ostream& operator<<(std::ostream&, const Light&) noexcept;

inline const glm::vec3& Light::getAmbient() const noexcept
{
    return m_ambient;
}

inline const glm::vec3& Light::getDiffuse() const noexcept
{
    return m_diffuse;
}

inline const glm::vec3& Light::getSpecular() const noexcept
{
    return m_specular;
}

inline float Light::getConstant() const noexcept
{
    return m_constant;
}

inline float Light::getLinear() const noexcept
{
    return m_linear;
}

inline float Light::getQuadratic() const noexcept
{
    return m_quadratic;
}

inline void Light::setAmbient(const glm::vec3& _ka) noexcept
{
    m_ambient = _ka;
}

inline void Light::setDiffuse(const glm::vec3& _kd) noexcept
{
    m_diffuse = _kd;
}

inline void Light::setSpecular(const glm::vec3& _ks) noexcept
{
    m_specular = _ks;
}

inline void Light::setConstant(float _const) noexcept
{
    m_constant = _const;
}

inline void Light::setLinear(float _linear) noexcept
{
    m_linear = _linear;
}

inline void Light::setQuadratic(float _quadratic) noexcept
{
    m_quadratic = _quadratic;
}

}
