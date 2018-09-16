#pragma once

#include "Light.hpp"

namespace Component
{

class DirectionalLight : public Light
{

public:

    DirectionalLight(const std::string&) noexcept;
    ~DirectionalLight() noexcept;
    DirectionalLight(const DirectionalLight&);
    DirectionalLight(DirectionalLight&&);
    DirectionalLight& operator=(const DirectionalLight&);
    DirectionalLight& operator=(DirectionalLight&&);

    std::ostream& print(std::ostream&) const noexcept;

    inline const glm::vec3& getDirection() const noexcept;

    inline void setDirection(const glm::vec3&) noexcept;

protected:

    glm::vec3 m_direction {1, 0, 0};

};

std::ostream& operator<<(std::ostream&, const DirectionalLight&) noexcept;

inline const glm::vec3& DirectionalLight::getDirection() const noexcept
{
    return m_direction;
}

inline void DirectionalLight::setDirection(const glm::vec3& _direction) noexcept
{
    m_direction = _direction;
}

}
