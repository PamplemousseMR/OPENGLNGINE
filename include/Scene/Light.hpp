#pragma once

#include "Commun/IPrintable.hpp"
#include "Scene/IMovableObject.hpp"

#include <glm/vec3.hpp>

#include <string>
#include <ostream>

namespace Scene
{

class Light final:
        public Commun::IPrintable<Light>,
        public IMovableObject
{

public:

    enum LIGHT_TYPE
    {
        LT_POINT,
        LT_DIRECTIONAL,
        LT_SPOTLIGHT
    };

    Light(LIGHT_TYPE = LT_POINT);
    Light(const std::string&, LIGHT_TYPE = LT_POINT);
    virtual ~Light() final;

    virtual std::ostream& print(std::ostream&) const final;

    inline LIGHT_TYPE getType() const;

    inline const glm::vec3& getAmbient() const;
    inline const glm::vec3& getDiffuse() const;
    inline const glm::vec3& getSpecular() const;
    inline float getConstant() const;
    inline float getLinear() const;
    inline float getQuadratic() const;
    inline const glm::vec3& getDirection() const;
    inline float getTheta() const;
    inline float getPhi() const;
    inline float getLambda() const;
    inline float getPhiCutoff() const;
    inline float getLambdaCutoff() const;

    inline void setAmbient(const glm::vec3&);
    inline void setDiffuse(const glm::vec3&);
    inline void setSpecular(const glm::vec3&);
    inline void setConstant(float);
    inline void setLinear(float);
    inline void setQuadratic(float);
    inline void setDirection(const glm::vec3&);
    inline void setTheta(float);
    inline void setPhi(float);
    inline void setLambda(float);
    inline void setPhiCutoff(float);
    inline void setLambdaCutoff(float);

private:

    Light(const Light&) = delete;
    Light(Light&&) = delete;
    Light& operator=(const Light&) = delete;
    Light& operator=(Light&&) = delete;

    LIGHT_TYPE m_type {LT_POINT};

    glm::vec3 m_ambient {1, 1, 1};
    glm::vec3 m_diffuse {1, 1, 1};
    glm::vec3 m_specular {1, 1, 1};
    float m_constant {1.0};
    float m_linear {1.0};
    float m_quadratic {1.0};

    glm::vec3 m_direction {1, 0, 0};

    float m_theta {45};
    float m_phi {40};
    float m_phiCutoff {0.9f};
    float m_lambda {35};
    float m_lambdaCutoff {0.8f};

};

inline Light::LIGHT_TYPE Light::getType() const
{
    return m_type;
}

inline const glm::vec3& Light::getAmbient() const
{
    return m_ambient;
}

inline const glm::vec3& Light::getDiffuse() const
{
    return m_diffuse;
}

inline const glm::vec3& Light::getSpecular() const
{
    return m_specular;
}

inline float Light::getConstant() const
{
    return m_constant;
}

inline float Light::getLinear() const
{
    return m_linear;
}

inline float Light::getQuadratic() const
{
    return m_quadratic;
}

inline const glm::vec3& Light::getDirection() const
{
    assert(m_type != LT_POINT && ("Point lights doesn't have direction"));
    return m_direction;
}

inline float Light::getTheta() const
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight have theta"));
    return m_theta;
}

inline float Light::getPhi() const
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight have phi"));
    return m_phi;
}

inline float Light::getLambda() const
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight have lambda"));
    return m_lambda;
}

inline float Light::getPhiCutoff() const
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight have phi cutoff"));
    return m_phiCutoff;
}

inline float Light::getLambdaCutoff() const
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight have lambda cutoff"));
    return m_lambdaCutoff;
}

inline void Light::setAmbient(const glm::vec3& _ka)
{
    m_ambient = _ka;
}

inline void Light::setDiffuse(const glm::vec3& _kd)
{
    m_diffuse = _kd;
}

inline void Light::setSpecular(const glm::vec3& _ks)
{
    m_specular = _ks;
}

inline void Light::setConstant(float _const)
{
    m_constant = _const;
}

inline void Light::setLinear(float _linear)
{
    m_linear = _linear;
}

inline void Light::setQuadratic(float _quadratic)
{
    m_quadratic = _quadratic;
}

inline void Light::setDirection(const glm::vec3& _direction)
{
    assert(m_type != LT_POINT && ("Point lights can have direction"));
    m_direction = _direction;
}

inline void Light::setTheta(float _angle)
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight can have theta"));
    m_theta = _angle;
}

inline void Light::setPhi(float _angle)
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight can have phi"));
    m_phi = _angle;
}

inline void Light::setLambda(float _angle)
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight can have lambda"));
    m_lambda = _angle;
}

inline void Light::setPhiCutoff(float _cutoff)
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight can have phi cutoff"));
    m_phiCutoff = _cutoff;
}

inline void Light::setLambdaCutoff(float _cutoff)
{
    assert(m_type == LT_SPOTLIGHT && ("Only spotlight can have lambda cutoff"));
    m_lambdaCutoff = _cutoff;
}

}
