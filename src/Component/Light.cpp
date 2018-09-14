#include "Component/Light.hpp"

using namespace std;
using namespace glm;

namespace Component
{

    Light::Light(const string& _name) noexcept :
        Component(_name)
    {
    }

    Light::~Light() noexcept
    {
    }

    ostream& Light::print(ostream& _o) const noexcept
    {
        _o << "[Light " << m_name << "]\n";
        _o << "\tambient : " << m_ambient[0] << " " << m_ambient[1] << " " << m_ambient[2] << "\n";
        _o << "\tdiffuse : " << m_diffuse[0] << " " << m_diffuse[1] << " " << m_diffuse[2] << "\n";
        _o << "\tspecular : " << m_specular[0] << " " << m_specular[1] << " " << m_specular[2] << "\n";
        _o << "\tconstant : " << m_constant << "\n";
        _o << "\tlinear : " << m_linear << "\n";
        _o << "\tquadratic : " << m_quadratic << "\n";
        return _o;
    }

    const vec3& Light::getAmbient() const noexcept
    {
        return m_ambient;
    }

    const vec3& Light::getDiffuse() const noexcept
    {
        return m_diffuse;
    }

    const vec3& Light::getSpecular() const noexcept
    {
        return m_specular;
    }

    float Light::getConstant() const noexcept
    {
        return m_constant;
    }

    float Light::getLinear() const noexcept
    {
        return m_linear;
    }

    float Light::getQuadratic() const noexcept
    {
        return m_quadratic;
    }

    void Light::setAmbient(const vec3& _ka) noexcept
    {
        m_ambient = _ka;
    }

    void Light::setDiffuse(const vec3& _kd) noexcept
    {
        m_diffuse = _kd;
    }

    void Light::setSpecular(const vec3& _ks) noexcept
    {
        m_specular = _ks;
    }

    void Light::setConstant(float _const) noexcept
    {
        m_constant = _const;
    }

    void Light::setLinear(float _linear) noexcept
    {
        m_linear = _linear;
    }

    void Light::setQuadratic(float _quadratic) noexcept
    {
        m_quadratic = _quadratic;
    }

    ostream& operator<<(ostream& _o, const Light& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
