#include "Component/SpotLight.hpp"

using namespace std;

namespace Component
{

    SpotLight::SpotLight(const string& _name) noexcept :
        DirectionalLight(_name)
    {
    }

    SpotLight::~SpotLight() noexcept
    {
    }

    ostream& SpotLight::print(ostream& _o) const noexcept
    {
        _o << "[SpotLight " << m_name << "]\n";
        _o << "\tambient : " << m_ambient[0] << " " << m_ambient[1] << " " << m_ambient[2] << "\n";
        _o << "\tdiffuse : " << m_diffuse[0] << " " << m_diffuse[1] << " " << m_diffuse[2] << "\n";
        _o << "\tspecular : " << m_specular[0] << " " << m_specular[1] << " " << m_specular[2] << "\n";
        _o << "\tconstant : " << m_constant << "\n";
        _o << "\tlinear : " << m_linear << "\n";
        _o << "\tquadratic : " << m_quadratic << "\n";
        _o << "\tdirection : " << m_direction[0] << " " << m_direction[1] << " " << m_direction[2] << "\n";
        _o << "\tangle : " << m_angle << "\n";
        return _o;
    }

    ostream& operator<<(ostream& _o, const SpotLight& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
