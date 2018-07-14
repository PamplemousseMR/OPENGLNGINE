#include "Asset/Material.hpp"
#include "Asset/Map.hpp"

using namespace std;
using namespace glm;

namespace Assets
{
    Material::Material(const string& name)
        : m_name(name),
        m_nsSpecularexponent(90.0f),
        m_kaAmbient(1, 1, 1),
        m_kdDiffuse(1, 1, 1),
        m_ksSpecular(1, 1, 1),
        m_tfTransmissionfilter(1, 1, 1),
        m_niOpticaldensity(1.0f),
        m_Ke(0, 0, 0),
        m_dDissolve(1.0f),
        m_halo(false),
        m_illumIllumination(2),
        m_sharpnessSharpness(60.0f),
        m_kaMap(nullptr),
        m_kdMap(nullptr),
        m_ksMap(nullptr),
        m_nsMap(nullptr),
        m_dMap(nullptr),
        m_dispMap(nullptr),
        m_decalMap(nullptr),
        m_bumpMap(nullptr)
    {
#ifdef _DEBUG
        cout << "[Material " << m_name << "] [Material(const string& name)]..." << endl;
        cout << "[Material " << m_name << "] [Material(const string& name)]...\tsuccess" << endl;
#endif
    }


    Material::~Material()
    {
#ifdef _DEBUG
        cout << "[Material " << m_name << "] [~Material()]..." << endl;
#endif
        if (m_kaMap)delete m_kaMap;
        if (m_kdMap)delete m_kdMap;
        if (m_ksMap)delete m_ksMap;
        if (m_nsMap)delete m_nsMap;
        if (m_dMap)delete m_dMap;
        if (m_dispMap)delete m_dispMap;
        if (m_decalMap)delete m_decalMap;
        if (m_bumpMap)delete m_bumpMap;
#ifdef _DEBUG
        cout << "[Material " << m_name << "] [~Material()]...\tsuccess" << endl;
#endif
    }

    ostream& Material::print(ostream& o) const
    {
        o << "[Material " << m_name << "]\n";
        o << "\tMaterial color & illumination statements :\n";
        o << "\t\tKa " << m_kaAmbient[0] << " " << m_kaAmbient[1] << " " << m_kaAmbient[2] << "\n";
        o << "\t\tKd " << m_kdDiffuse[0] << " " << m_kdDiffuse[1] << " " << m_kdDiffuse[2] << "\n";
        o << "\t\tKs " << m_ksSpecular[0] << " " << m_ksSpecular[1] << " " << m_ksSpecular[2] << "\n";
        o << "\t\tTf " << m_tfTransmissionfilter[0] << " " << m_tfTransmissionfilter[1] << " " << m_tfTransmissionfilter[2] << "\n";
        o << "\t\tilum " << m_illumIllumination << "\n";
        o << "\t\td " << m_dDissolve << "\n";
        o << "\t\tNs " << m_nsSpecularexponent << "\n";
        o << "\t\tsharpness " << m_sharpnessSharpness << "\n";
        o << "\t\tNi " << m_niOpticaldensity << "\n";
        o << "\treflection map statement :\n";
        o << "\ttodo\n";
        return o;
    }

    const string& Material::getName() const
    {
        return m_name;
    }

    const vec3& Material::getAmbient() const
    {
        return m_kaAmbient;
    }

    const vec3& Material::getDiffuse() const
    {
        return m_kdDiffuse;
    }

    const vec3& Material::getSpecular() const
    {
        return m_ksSpecular;
    }

    const vec3& Material::getTransmissionFilter() const
    {
        return m_tfTransmissionfilter;
    }

    int Material::getIllumination() const
    {
        return m_illumIllumination;
    }

    float Material::getDissolve() const
    {
        return m_dDissolve;
    }

    bool Material::getHalo() const
    {
        return m_halo;
    }

    float Material::getSpecularExponent() const
    {
        return m_nsSpecularexponent;
    }

    float Material::getSharpness() const
    {
        return m_sharpnessSharpness;
    }

    float Material::getopticalDensity() const
    {
        return m_niOpticaldensity;
    }


    Map* Material::getKamap() const
    {
        return m_kaMap;
    }

    Map* Material::getKdmap() const
    {
        return m_kdMap;
    }

    Map* Material::getKsmap() const
    {
        return m_ksMap;
    }

    Map* Material::getNsmap() const
    {
        return m_nsMap;
    }

    Map* Material::getdmap() const
    {
        return m_dMap;
    }

    Map* Material::getDispmap() const
    {
        return m_dispMap;
    }

    Map* Material::getDecalmap() const
    {
        return m_decalMap;
    }

    Map* Material::getBumpmap() const
    {
        return m_bumpMap;
    }

    void Material::setAmbient(const vec3& ka)
    {
        m_kaAmbient = ka;
    }

    void Material::setDiffuse(const vec3& kd)
    {
        m_kdDiffuse = kd;
    }

    void Material::setSpecular(const vec3& ks)
    {
        m_ksSpecular = ks;
    }

    void Material::setTransmissionFilter(const vec3& tf)
    {
        m_tfTransmissionfilter = tf;
    }

    void Material::setIllumination(int illum)
    {
        m_illumIllumination = illum;
    }

    void Material::setDissolve(float d)
    {
        m_dDissolve = d;
    }

    void Material::setHalo(bool h)
    {
        m_halo = h;
    }

    void Material::setSpecularExponent(float ns)
    {
        m_nsSpecularexponent = ns;
    }

    void Material::setSharpness(float sharp)
    {
        m_sharpnessSharpness = sharp;
    }

    void Material::setopticalDensity(float ni)
    {
        m_niOpticaldensity = ni;
    }

    void Material::setEmissiveCoeficient(const vec3& ke)
    {
        m_Ke = ke;
    }


    void Material::setKamap(const string& path) throw()
    {
        if (m_kaMap)delete m_kaMap;
        try {
            m_kaMap = new Map(MAP_TYPE::Ka, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setKamap(const string& path) throw()] " + e.what());
        }
    }

    void Material::setKdmap(const string& path) throw()
    {
        if (m_kdMap)delete m_kdMap;
        try {
            m_kdMap = new Map(MAP_TYPE::Kd, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setKdmap(const string& path) throw()] " + e.what());
        }
    }

    void Material::setKsmap(const string& path) throw()
    {
        if (m_ksMap)delete m_ksMap;
        try {
            m_ksMap = new Map(MAP_TYPE::Ks, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setKsmap(const string& path) throw()] " + e.what());
        }
    }

    void Material::setNsmap(const string& path) throw()
    {
        if (m_nsMap)delete m_nsMap;
        try {
            m_nsMap = new Map(MAP_TYPE::Ns, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setNsmap(const string& path) throw()] " + e.what());
        }
    }

    void Material::setdmap(const string& path) throw()
    {
        if (m_dMap)delete m_dMap;
        try {
            m_dMap = new Map(MAP_TYPE::d, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setdmap(const string& path) throw()] " + e.what());
        }
    }

    void Material::setDispmap(const string& path) throw()
    {
        if (m_dispMap)delete m_dispMap;
        try {
            m_dispMap = new Map(MAP_TYPE::disp, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setDispmap(const string& path) throw()] " + e.what());
        }
    }

    void Material::setDecalmap(const string& path) throw()
    {
        if (m_decalMap)delete m_decalMap;
        try {
            m_decalMap = new Map(MAP_TYPE::decal, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setDecalmap(const string& path) throw()] " + e.what());
        }
    }

    void Material::setBumpmap(const string& path) throw()
    {
        if (m_bumpMap)delete m_bumpMap;
        try {
            m_bumpMap = new Map(MAP_TYPE::bump, path);
        }
        catch (exception e) {
            throw invalid_argument("[Material " + m_name + "] [setBumpmap(const string& path) throw()] " + e.what());
        }
    }


    ostream& operator<<(ostream& o, const Material& m)
    {
        m.print(o);
        return o;
    }

}
