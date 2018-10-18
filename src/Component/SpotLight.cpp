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

    SpotLight::SpotLight(const SpotLight& _light) :
        DirectionalLight(_light),
        m_theta(_light.m_theta),
        m_phi(_light.m_phi),
        m_phiCutoff(_light.m_phiCutoff),
        m_lambda(_light.m_lambda),
        m_lambdaCutoff(_light.m_lambdaCutoff)
    {
    }

    SpotLight::SpotLight(SpotLight&& _light) :
        DirectionalLight(move(_light)),
        m_theta(move(_light.m_theta)),
        m_phi(move(_light.m_phi)),
        m_phiCutoff(move(_light.m_phiCutoff)),
        m_lambda(move(_light.m_lambda)),
        m_lambdaCutoff(move(_light.m_lambdaCutoff))
    {
    }

    SpotLight& SpotLight::operator=(const SpotLight& _light)
    {
        if(this != &_light)
        {
            DirectionalLight::operator=(_light);
            m_theta = _light.m_theta;
            m_phi = _light.m_phi;
            m_phiCutoff = _light.m_phiCutoff;
            m_lambda = _light.m_lambda;
            m_lambdaCutoff = _light.m_lambdaCutoff;
        }
        return *this;
    }

    SpotLight& SpotLight::operator=(SpotLight&& _light)
    {
        if(this != &_light)
        {
            DirectionalLight::operator=(move(_light));
            m_theta = move(_light.m_theta);
            m_phi = move(_light.m_phi);
            m_phiCutoff = move(_light.m_phiCutoff);
            m_lambda = move(_light.m_lambda);
            m_lambdaCutoff = move(_light.m_lambdaCutoff);
        }
        return *this;
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
        _o << "\ttheta : " << m_theta << "\n";
        _o << "\tphi : " << m_phi << "\n";
        _o << "\tlamdba : " << m_lambda << "\n";
        _o << "\tphiCutoff : " << m_phiCutoff << "\n";
        _o << "\tlambdaCutoff : " << m_lambdaCutoff << "\n";
        return _o;
    }

    ostream& operator<<(ostream& _o, const SpotLight& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
