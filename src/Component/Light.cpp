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

    ostream& operator<<(ostream& _o, const Light& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
