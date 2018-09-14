#pragma once

#include "Light.hpp"

namespace Component
{

class DirectionalLight : public Light
{

public:

    DirectionalLight(const std::string&) noexcept;
    ~DirectionalLight() noexcept;

    std::ostream& print(std::ostream&) const noexcept;

    const glm::vec3& getDirection() const noexcept;

    void setDirection(const glm::vec3&) noexcept;

protected:

    glm::vec3 m_direction {1, 0, 0};

};

std::ostream& operator<<(std::ostream&, const DirectionalLight&) noexcept;

}
