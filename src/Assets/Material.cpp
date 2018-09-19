#include "Assets/Material.hpp"
#include "Assets/Map.hpp"

using namespace std;
using namespace glm;

namespace Assets
{
    Material::Material(const string& _name) noexcept :
        m_name(_name)
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

    Material::Material(const Material& _mat) :
        m_name(_mat.m_name),
        m_kaAmbient(_mat.m_kaAmbient),
        m_kdDiffuse(_mat.m_kdDiffuse),
        m_ksSpecular(_mat.m_ksSpecular),
        m_tfTransmissionfilter(_mat.m_tfTransmissionfilter),
        m_illumIllumination(_mat.m_illumIllumination),
        m_dDissolve(_mat.m_dDissolve),
        m_halo(_mat.m_halo),
        m_nsSpecularexponent(_mat.m_nsSpecularexponent),
        m_sharpnessSharpness(_mat.m_sharpnessSharpness),
        m_niOpticaldensity(_mat.m_niOpticaldensity),
        m_Ke(_mat.m_Ke),
        m_kaMap(_mat.m_kaMap != nullptr ? new Map(*_mat.m_kaMap) : nullptr),
        m_kdMap(_mat.m_kdMap != nullptr ? new Map(*_mat.m_kdMap) : nullptr),
        m_ksMap(_mat.m_ksMap != nullptr ? new Map(*_mat.m_ksMap) : nullptr),
        m_nsMap(_mat.m_nsMap != nullptr ? new Map(*_mat.m_nsMap) : nullptr),
        m_dMap(_mat.m_dMap != nullptr ? new Map(*_mat.m_dMap) : nullptr),
        m_dispMap(_mat.m_dispMap != nullptr ? new Map(*_mat.m_dispMap) : nullptr),
        m_decalMap(_mat.m_decalMap != nullptr ? new Map(*_mat.m_decalMap) : nullptr),
        m_bumpMap(_mat.m_bumpMap != nullptr ? new Map(*_mat.m_bumpMap) : nullptr)
    {
    }

    Material::Material(Material&& _mat) :
       m_name(std::move(_mat.m_name)),
       m_kaAmbient(std::move(_mat.m_kaAmbient)),
       m_kdDiffuse(std::move(_mat.m_kdDiffuse)),
       m_ksSpecular(std::move(_mat.m_ksSpecular)),
       m_tfTransmissionfilter(std::move(_mat.m_tfTransmissionfilter)),
       m_illumIllumination(std::move(_mat.m_illumIllumination)),
       m_dDissolve(std::move(_mat.m_dDissolve)),
       m_halo(std::move(_mat.m_halo)),
       m_nsSpecularexponent(std::move(_mat.m_nsSpecularexponent)),
       m_sharpnessSharpness(std::move(_mat.m_sharpnessSharpness)),
       m_niOpticaldensity(std::move(_mat.m_niOpticaldensity)),
       m_Ke(std::move(_mat.m_Ke))
   {
       m_kaMap = _mat.m_kaMap;
       _mat.m_kaMap = nullptr;
       m_kdMap = _mat.m_kdMap;
       _mat.m_kdMap = nullptr;
       m_ksMap = _mat.m_ksMap;
       _mat.m_ksMap = nullptr;
       m_nsMap = _mat.m_nsMap;
       _mat.m_nsMap = nullptr;
       m_dMap = _mat.m_dMap;
       _mat.m_dMap = nullptr;
       m_dispMap = _mat.m_dispMap;
       _mat.m_dispMap = nullptr;
       m_decalMap = _mat.m_decalMap;
       _mat.m_decalMap = nullptr;
       m_bumpMap = _mat.m_bumpMap;
       _mat.m_bumpMap = nullptr;
   }

    Material& Material::operator=(const Material& _mat)
    {
        if(this != &_mat)
        {
            if (m_kaMap)delete m_kaMap;
            if (m_kdMap)delete m_kdMap;
            if (m_ksMap)delete m_ksMap;
            if (m_nsMap)delete m_nsMap;
            if (m_dMap)delete m_dMap;
            if (m_dispMap)delete m_dispMap;
            if (m_decalMap)delete m_decalMap;
            if (m_bumpMap)delete m_bumpMap;

            m_name = _mat.m_name;
            m_kaAmbient = _mat.m_kaAmbient;
            m_kdDiffuse = _mat.m_kdDiffuse;
            m_ksSpecular = _mat.m_ksSpecular;
            m_tfTransmissionfilter = _mat.m_tfTransmissionfilter;
            m_illumIllumination = _mat.m_illumIllumination;
            m_dDissolve = _mat.m_dDissolve;
            m_halo = _mat.m_halo;
            m_nsSpecularexponent = _mat.m_nsSpecularexponent;
            m_sharpnessSharpness = _mat.m_sharpnessSharpness;
            m_niOpticaldensity = _mat.m_niOpticaldensity;
            m_Ke = _mat.m_Ke;
            m_kaMap = new Map(*_mat.m_kaMap);
            m_kdMap = new Map(*_mat.m_kdMap);
            m_ksMap = new Map(*_mat.m_ksMap);
            m_nsMap = new Map(*_mat.m_nsMap);
            m_dMap = new Map(*_mat.m_dMap);
            m_dispMap = new Map(*_mat.m_dispMap);
            m_decalMap = new Map(*_mat.m_decalMap);
            m_bumpMap = new Map(*_mat.m_bumpMap);
        }
        return *this;
    }

    Material& Material::operator=(Material&& _mat)
    {
        if(this != &_mat)
        {
            if (m_kaMap)delete m_kaMap;
            if (m_kdMap)delete m_kdMap;
            if (m_ksMap)delete m_ksMap;
            if (m_nsMap)delete m_nsMap;
            if (m_dMap)delete m_dMap;
            if (m_dispMap)delete m_dispMap;
            if (m_decalMap)delete m_decalMap;
            if (m_bumpMap)delete m_bumpMap;

            m_name = std::move(_mat.m_name);
            m_kaAmbient = std::move(_mat.m_kaAmbient);
            m_kdDiffuse = std::move(_mat.m_kdDiffuse);
            m_ksSpecular = std::move(_mat.m_ksSpecular);
            m_tfTransmissionfilter = std::move(_mat.m_tfTransmissionfilter);
            m_illumIllumination = std::move(_mat.m_illumIllumination);
            m_dDissolve = std::move(_mat.m_dDissolve);
            m_halo = std::move(_mat.m_halo);
            m_nsSpecularexponent = std::move(_mat.m_nsSpecularexponent);
            m_sharpnessSharpness = std::move(_mat.m_sharpnessSharpness);
            m_niOpticaldensity = std::move(_mat.m_niOpticaldensity);
            m_Ke = std::move(_mat.m_Ke);

            m_kaMap = _mat.m_kaMap;
            _mat.m_kaMap = nullptr;
            m_kdMap = _mat.m_kdMap;
            _mat.m_kdMap = nullptr;
            m_ksMap = _mat.m_ksMap;
            _mat.m_ksMap = nullptr;
            m_nsMap = _mat.m_nsMap;
            _mat.m_nsMap = nullptr;
            m_dMap = _mat.m_dMap;
            _mat.m_dMap = nullptr;
            m_dispMap = _mat.m_dispMap;
            _mat.m_dispMap = nullptr;
            m_decalMap = _mat.m_decalMap;
            _mat.m_decalMap = nullptr;
            m_bumpMap = _mat.m_bumpMap;
            _mat.m_bumpMap = nullptr;
        }
        return *this;
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
        return _o;
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

    void Material::setKamap(const std::filesystem::path& _path)
    {
        if (m_kaMap)
        {
            delete m_kaMap;
        }
        m_kaMap = new Map(Map::KA, _path);
    }

    void Material::setKdmap(const std::filesystem::path& _path)
    {
        if (m_kdMap)
        {
            delete m_kdMap;
        }
        m_kdMap = new Map(Map::KD, _path);
    }

    void Material::setKsmap(const std::filesystem::path& _path)
    {
        if (m_ksMap)
        {
            delete m_ksMap;
        }
        m_ksMap = new Map(Map::KS, _path);
    }

    void Material::setNsmap(const std::filesystem::path& _path)
    {
        if (m_nsMap)
        {
            delete m_nsMap;
        }
        m_nsMap = new Map(Map::NS, _path);
    }

    void Material::setdmap(const std::filesystem::path& _path)
    {
        if (m_dMap)
        {
            delete m_dMap;
        }
        m_dMap = new Map(Map::D, _path);
    }

    void Material::setDispmap(const std::filesystem::path& _path)
    {
        if (m_dispMap)
        {
            delete m_dispMap;
        }
        m_dispMap = new Map(Map::DISP, _path);
    }

    void Material::setDecalmap(const std::filesystem::path& _path)
    {
        if (m_decalMap)
        {
            delete m_decalMap;
        }
        m_decalMap = new Map(Map::DECAL, _path);
    }

    void Material::setBumpmap(const std::filesystem::path& _path)
    {
        if (m_bumpMap)
        {
            delete m_bumpMap;
        }
        m_bumpMap = new Map(Map::BUMP, _path);
    }


    ostream& operator<<(ostream& _o, const Material& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }

}
