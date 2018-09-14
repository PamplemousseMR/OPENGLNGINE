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

    float getAngle() const noexcept;

    void setAngle(float) noexcept;

private:

    float m_angle {45};

};

std::ostream& operator<<(std::ostream&, const SpotLight&) noexcept;

}
