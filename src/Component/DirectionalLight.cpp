#include "Component/DirectionalLight.hpp"

using namespace std;
using namespace glm;

namespace Component
{

    DirectionalLight::DirectionalLight(const string& _name) noexcept :
        Light(_name)
    {
    }

    DirectionalLight::~DirectionalLight() noexcept
    {
    }

    ostream& DirectionalLight::print(ostream& _o) const noexcept
    {
        _o << "[DirectionalLight " << m_name << "]\n";
        _o << "\tambient : " << m_ambient[0] << " " << m_ambient[1] << " " << m_ambient[2] << "\n";
        _o << "\tdiffuse : " << m_diffuse[0] << " " << m_diffuse[1] << " " << m_diffuse[2] << "\n";
        _o << "\tspecular : " << m_specular[0] << " " << m_specular[1] << " " << m_specular[2] << "\n";
        _o << "\tconstant : " << m_constant << "\n";
        _o << "\tlinear : " << m_linear << "\n";
        _o << "\tquadratic : " << m_quadratic << "\n";
        _o << "\tdirection : " << m_direction[0] << " " << m_direction[1] << " " << m_direction[2] << "\n";
        return _o;
    }

    ostream& operator<<(ostream& _o, const DirectionalLight& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
