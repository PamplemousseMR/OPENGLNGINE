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

    const glm::vec3& getAmbient() const noexcept;
    const glm::vec3& getDiffuse() const noexcept;
    const glm::vec3& getSpecular() const noexcept;
    float getConstant() const noexcept;
    float getLinear() const noexcept;
    float getQuadratic() const noexcept;

    void setAmbient(const glm::vec3&) noexcept;
    void setDiffuse(const glm::vec3&) noexcept;
    void setSpecular(const glm::vec3&) noexcept;
    void setConstant(float) noexcept;
    void setLinear(float) noexcept;
    void setQuadratic(float) noexcept;

protected:

    glm::vec3 m_ambient {1, 1, 1};
    glm::vec3 m_diffuse {1, 1, 1};
    glm::vec3 m_specular {1, 1, 1};
    float m_constant {1.0};
    float m_linear {1.0};
    float m_quadratic {1.0};

};

std::ostream& operator<<(std::ostream&, const Light&) noexcept;

}
