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
        try
        {
            m_kaMap = new Map(Map::KA, _path);
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
            m_kdMap = new Map(Map::KD, _path);
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
            m_ksMap = new Map(Map::KS, _path);
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
            m_nsMap = new Map(Map::NS, _path);
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
            m_dMap = new Map(Map::D, _path);
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
            m_dispMap = new Map(Map::DISP, _path);
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
            m_decalMap = new Map(Map::DECAL, _path);
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
            m_bumpMap = new Map(Map::BUMP, _path);
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
