#include "Asset/Material.hpp"
#include "Asset/Map.hpp"

using namespace std;
using namespace glm;

namespace Assets
{
    Material::Material(const string& _name) noexcept :
        m_name(_name),
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
    }

    Material::~Material() noexcept
    {
        if (m_kaMap)delete m_kaMap;
        if (m_kdMap)delete m_kdMap;
        if (m_ksMap)delete m_ksMap;
        if (m_nsMap)delete m_nsMap;
        if (m_dMap)delete m_dMap;
        if (m_dispMap)delete m_dispMap;
        if (m_decalMap)delete m_decalMap;
        if (m_bumpMap)delete m_bumpMap;
    }

    ostream& Material::print(ostream& _o) const noexcept
    {
        _o << "[Material " << m_name << "]\n";
        _o << "\tMaterial color & illumination statements :\n";
        _o << "\t\tKa " << m_kaAmbient[0] << " " << m_kaAmbient[1] << " " << m_kaAmbient[2] << "\n";
        _o << "\t\tKd " << m_kdDiffuse[0] << " " << m_kdDiffuse[1] << " " << m_kdDiffuse[2] << "\n";
        _o << "\t\tKs " << m_ksSpecular[0] << " " << m_ksSpecular[1] << " " << m_ksSpecular[2] << "\n";
        _o << "\t\tTf " << m_tfTransmissionfilter[0] << " " << m_tfTransmissionfilter[1] << " " << m_tfTransmissionfilter[2] << "\n";
        _o << "\t\tilum " << m_illumIllumination << "\n";
        _o << "\t\td " << m_dDissolve << "\n";
        _o << "\t\tNs " << m_nsSpecularexponent << "\n";
        _o << "\t\tsharpness " << m_sharpnessSharpness << "\n";
        _o << "\t\tNi " << m_niOpticaldensity << "\n";
        _o << "\treflection map statement :\n";
        _o << "\ttodo\n";
        return _o;
    }

    const string& Material::getName() const noexcept
    {
        return m_name;
    }

    const vec3& Material::getAmbient() const noexcept
    {
        return m_kaAmbient;
    }

    const vec3& Material::getDiffuse() const noexcept
    {
        return m_kdDiffuse;
    }

    const vec3& Material::getSpecular() const noexcept
    {
        return m_ksSpecular;
    }

    const vec3& Material::getTransmissionFilter() const noexcept
    {
        return m_tfTransmissionfilter;
    }

    int Material::getIllumination() const noexcept
    {
        return m_illumIllumination;
    }

    float Material::getDissolve() const noexcept
    {
        return m_dDissolve;
    }

    bool Material::getHalo() const noexcept
    {
        return m_halo;
    }

    float Material::getSpecularExponent() const noexcept
    {
        return m_nsSpecularexponent;
    }

    float Material::getSharpness() const noexcept
    {
        return m_sharpnessSharpness;
    }

    float Material::getopticalDensity() const noexcept
    {
        return m_niOpticaldensity;
    }


    Map* Material::getKamap() const noexcept
    {
        return m_kaMap;
    }

    Map* Material::getKdmap() const noexcept
    {
        return m_kdMap;
    }

    Map* Material::getKsmap() const noexcept
    {
        return m_ksMap;
    }

    Map* Material::getNsmap() const noexcept
    {
        return m_nsMap;
    }

    Map* Material::getdmap() const noexcept
    {
        return m_dMap;
    }

    Map* Material::getDispmap() const noexcept
    {
        return m_dispMap;
    }

    Map* Material::getDecalmap() const noexcept
    {
        return m_decalMap;
    }

    Map* Material::getBumpmap() const noexcept
    {
        return m_bumpMap;
    }

    void Material::setAmbient(const vec3& _ka) noexcept
    {
        m_kaAmbient = _ka;
    }

    void Material::setDiffuse(const vec3& _kd) noexcept
    {
        m_kdDiffuse = _kd;
    }

    void Material::setSpecular(const vec3& _ks) noexcept
    {
        m_ksSpecular = _ks;
    }

    void Material::setTransmissionFilter(const vec3& _tf) noexcept
    {
        m_tfTransmissionfilter = _tf;
    }

    void Material::setIllumination(int _illum) noexcept
    {
        m_illumIllumination = _illum;
    }

    void Material::setDissolve(float _d) noexcept
    {
        m_dDissolve = _d;
    }

    void Material::setHalo(bool _h) noexcept
    {
        m_halo = _h;
    }

    void Material::setSpecularExponent(float _ns) noexcept
    {
        m_nsSpecularexponent = _ns;
    }

    void Material::setSharpness(float _sharp) noexcept
    {
        m_sharpnessSharpness = _sharp;
    }

    void Material::setopticalDensity(float _ni) noexcept
    {
        m_niOpticaldensity = _ni;
    }

    void Material::setEmissiveCoeficient(const vec3& _ke) noexcept
    {
        m_Ke = _ke;
    }

    void Material::setKamap(const std::filesystem::path& _path)
    {
        if (m_kaMap)
        {
            delete m_kaMap;
        }
        try
        {
            m_kaMap = new Map(MAP_TYPE::Ka, _path);
        }
        catch (const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }

    void Material::setKdmap(const std::filesystem::path& _path)
    {
        if (m_kdMap)
        {
            delete m_kdMap;
        }
        try
        {
            m_kdMap = new Map(MAP_TYPE::Kd, _path);
        }
        catch (const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }

    void Material::setKsmap(const std::filesystem::path& _path)
    {
        if (m_ksMap)
        {
            delete m_ksMap;
        }
        try
        {
            m_ksMap = new Map(MAP_TYPE::Ks, _path);
        }
        catch (const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }

    void Material::setNsmap(const std::filesystem::path& _path)
    {
        if (m_nsMap)
        {
            delete m_nsMap;
        }
        try
        {
            m_nsMap = new Map(MAP_TYPE::Ns, _path);
        }
        catch (const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }

    void Material::setdmap(const std::filesystem::path& _path)
    {
        if (m_dMap)
        {
            delete m_dMap;
        }
        try
        {
            m_dMap = new Map(MAP_TYPE::d, _path);
        }
        catch (const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }

    void Material::setDispmap(const std::filesystem::path& _path)
    {
        if (m_dispMap)
        {
            delete m_dispMap;
        }
        try
        {
            m_dispMap = new Map(MAP_TYPE::disp, _path);
        }
        catch(const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }

    void Material::setDecalmap(const std::filesystem::path& _path)
    {
        if (m_decalMap)
        {
            delete m_decalMap;
        }
        try
        {
            m_decalMap = new Map(MAP_TYPE::decal, _path);
        }
        catch(const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }

    void Material::setBumpmap(const std::filesystem::path& _path)
    {
        if (m_bumpMap)
        {
            delete m_bumpMap;
        }
        try
        {
            m_bumpMap = new Map(MAP_TYPE::bump, _path);
        }
        catch (const exception& _e)
        {
            throw invalid_argument("[Material] " + string(_e.what()));
        }
    }


    ostream& operator<<(ostream& _o, const Material& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }

}
