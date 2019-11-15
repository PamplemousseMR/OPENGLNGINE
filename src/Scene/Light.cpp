#include "Scene/Light.hpp"

using namespace Commun;
using namespace std;

namespace Scene
{

    const std::string IMovableObject::s_FACTORY_TYPE_NAME = "Light";

    Light::Light(LIGHT_TYPE _type) :
        IPrintable(),
        IMovableObject(),
        m_type(_type)
    {
    }

    Light::Light(const string& _name, LIGHT_TYPE _type) :
        IPrintable(),
        IMovableObject(_name),
        m_type(_type)
    {
    }

    Light::~Light()
    {
    }

    ostream& Light::print(ostream& _o) const
    {
        string type;
        switch (m_type)
        {
        case LT_POINT:
            type = "LT_POINT";
            break;
        case LT_DIRECTIONAL:
            type = "LT_DIRECTIONAL";
            break;
        case LT_SPOTLIGHT:
            type = "LT_SPOTLIGHT";
            break;
        default:
            type = "ERROR";
            break;
        }

        _o << "[Light(" << type << ") " << m_name << "]" << endl;
        _o << "\tambient : " << m_ambient[0] << " " << m_ambient[1] << " " << m_ambient[2] << endl;
        _o << "\tdiffuse : " << m_diffuse[0] << " " << m_diffuse[1] << " " << m_diffuse[2] << endl;
        _o << "\tspecular : " << m_specular[0] << " " << m_specular[1] << " " << m_specular[2] << endl;
        _o << "\tconstant : " << m_constant << endl;
        _o << "\tlinear : " << m_linear << endl;
        _o << "\tquadratic : " << m_quadratic << endl;

        if(m_type == LT_DIRECTIONAL)
        {
            _o << "\tdirection : " << m_direction[0] << " " << m_direction[1] << " " << m_direction[2] << endl;
        }

        if(m_type == LT_SPOTLIGHT)
        {
            _o << "\ttheta : " << m_theta << endl;
            _o << "\tphi : " << m_phi << endl;
            _o << "\tlamdba : " << m_lambda << endl;
            _o << "\tphiCutoff : " << m_phiCutoff << endl;
            _o << "\tlambdaCutoff : " << m_lambdaCutoff << endl;
        }

        return _o;
    }

}
