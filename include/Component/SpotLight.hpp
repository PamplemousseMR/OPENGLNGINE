#pragma once

#include "DirectionalLight.hpp"

namespace Component
{

class SpotLight : public DirectionalLight
{

public:

    SpotLight(const std::string&) noexcept;
    ~SpotLight() noexcept;

    std::ostream& print(std::ostream&) const noexcept;

    inline float getAngle() const noexcept;

    inline void setAngle(float) noexcept;

private:

    float m_angle {45};

};

std::ostream& operator<<(std::ostream&, const SpotLight&) noexcept;

inline float SpotLight::getAngle() const noexcept
{
    return m_angle;
}

inline void SpotLight::setAngle(float _angle) noexcept
{
    m_angle = _angle;
}

}
