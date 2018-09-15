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

    inline float getTheta() const noexcept;
    inline float getPhi() const noexcept;
    inline float getLambda() const noexcept;
    inline float getPhiCutoff() const noexcept;
    inline float getLambdaCutoff() const noexcept;

    inline void setTheta(float) noexcept;
    inline void setPhi(float) noexcept;
    inline void setLambda(float) noexcept;
    inline void setPhiCutoff(float) noexcept;
    inline void setLambdaCutoff(float) noexcept;
private:

    float m_theta {45};
    float m_phi {40};
    float m_phiCutoff {0.9f};
    float m_lambda {35};
    float m_lambdaCutoff {0.8f};

};

std::ostream& operator<<(std::ostream&, const SpotLight&) noexcept;

inline float SpotLight::getTheta() const noexcept
{
    return m_theta;
}

inline float SpotLight::getPhi() const noexcept
{
    return m_phi;
}

inline float SpotLight::getLambda() const noexcept
{
    return m_lambda;
}

inline float SpotLight::getPhiCutoff() const noexcept
{
    return m_phiCutoff;
}

inline float SpotLight::getLambdaCutoff() const noexcept
{
    return m_lambdaCutoff;
}

inline void SpotLight::setTheta(float _angle) noexcept
{
    m_theta = _angle;
}

inline void SpotLight::setPhi(float _angle) noexcept
{
    m_phi = _angle;
}

inline void SpotLight::setLambda(float _angle) noexcept
{
    m_lambda = _angle;
}

inline void SpotLight::setPhiCutoff(float _cutoff) noexcept
{
    m_phiCutoff = _cutoff;
}

inline void SpotLight::setLambdaCutoff(float _cutoff) noexcept
{
    m_lambdaCutoff = _cutoff;
}

}
