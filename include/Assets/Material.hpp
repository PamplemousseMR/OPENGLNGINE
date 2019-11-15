#pragma once

#include <glm/vec3.hpp>

#include <filesystem>
#include <iostream>
#include <string>

namespace GL
{
    class Texture;
}

namespace Assets
{
class Map;

class Material
{

public:

    Material(const std::string&);
    ~Material();
    Material(const Material&);
    Material(Material&&);
    Material& operator=(const Material&);
    Material& operator=(Material&&);

    inline const std::string& getName() const;
    inline const glm::vec3& getAmbient() const;
    inline const glm::vec3& getDiffuse() const;
    inline const glm::vec3& getSpecular() const;
    inline const glm::vec3& getTransmissionFilter() const;
    inline int getIllumination() const;
    inline float getDissolve() const;
    inline bool getHalo() const;
    inline float getSpecularExponent() const;
    inline float getSharpness() const;
    inline float getopticalDensity() const;
    Map* getKamap() const;
    Map* getKdmap() const;
    Map* getKsmap() const;
    Map* getNsmap() const;
    Map* getdmap() const;
    Map* getDecalmap() const;
    Map* getDispmap() const;
    Map* getBumpmap() const;

    inline void setAmbient(const glm::vec3&);
    inline void setDiffuse(const glm::vec3&);
    inline void setSpecular(const glm::vec3&);
    inline void setTransmissionFilter(const glm::vec3&);
    inline void setIllumination(int);
    inline void setDissolve(float);
    inline void setHalo(bool);
    inline void setSpecularExponent(float);
    inline void setSharpness(float);
    inline void setopticalDensity(float);
    inline void setEmissiveCoeficient(const glm::vec3&);
    void setKamap(const std::filesystem::path&);
    void setKdmap(const std::filesystem::path&);
    void setKsmap(const std::filesystem::path&);
    void setNsmap(const std::filesystem::path&);
    void setdmap(const std::filesystem::path&);
    void setDecalmap(const std::filesystem::path&);
    void setDispmap(const std::filesystem::path&);
    void setBumpmap(const std::filesystem::path&);

    std::ostream& print(std::ostream&) const;

private :

    std::string m_name {};
    glm::vec3 m_kaAmbient {1, 1, 1};
    glm::vec3 m_kdDiffuse {1, 1, 1};
    glm::vec3 m_ksSpecular {1, 1, 1};
    glm::vec3 m_tfTransmissionfilter {1, 1, 1};
    int m_illumIllumination {2};
    float m_dDissolve {1.0f};
    bool m_halo {false};
    float m_nsSpecularexponent {90.0f};
    float m_sharpnessSharpness {60.0f};
    float m_niOpticaldensity {1.0f};
    glm::vec3 m_Ke {0, 0, 0};
    Map* m_kaMap {nullptr};
    Map* m_kdMap {nullptr};
    Map* m_ksMap {nullptr};
    Map* m_nsMap {nullptr};
    Map* m_dMap {nullptr};
    Map* m_dispMap {nullptr};
    Map* m_decalMap {nullptr};
    Map* m_bumpMap {nullptr};

};

std::ostream& operator<<(std::ostream&, const Material&);

inline const std::string& Material::getName() const
{
    return m_name;
}

inline const glm::vec3& Material::getAmbient() const
{
    return m_kaAmbient;
}

inline const glm::vec3& Material::getDiffuse() const
{
    return m_kdDiffuse;
}

inline const glm::vec3& Material::getSpecular() const
{
    return m_ksSpecular;
}

inline const glm::vec3& Material::getTransmissionFilter() const
{
    return m_tfTransmissionfilter;
}

inline int Material::getIllumination() const
{
    return m_illumIllumination;
}

inline float Material::getDissolve() const
{
    return m_dDissolve;
}

inline bool Material::getHalo() const
{
    return m_halo;
}

inline float Material::getSpecularExponent() const
{
    return m_nsSpecularexponent;
}

inline float Material::getSharpness() const
{
    return m_sharpnessSharpness;
}

inline float Material::getopticalDensity() const
{
    return m_niOpticaldensity;
}

inline void Material::setAmbient(const glm::vec3& _ka)
{
    m_kaAmbient = _ka;
}

inline void Material::setDiffuse(const glm::vec3& _kd)
{
    m_kdDiffuse = _kd;
}

inline void Material::setSpecular(const glm::vec3& _ks)
{
    m_ksSpecular = _ks;
}

inline void Material::setTransmissionFilter(const glm::vec3& _tf)
{
    m_tfTransmissionfilter = _tf;
}

inline void Material::setIllumination(int _illum)
{
    m_illumIllumination = _illum;
}

inline void Material::setDissolve(float _d)
{
    m_dDissolve = _d;
}

inline void Material::setHalo(bool _h)
{
    m_halo = _h;
}

inline void Material::setSpecularExponent(float _ns)
{
    m_nsSpecularexponent = _ns;
}

inline void Material::setSharpness(float _sharp)
{
    m_sharpnessSharpness = _sharp;
}

inline void Material::setopticalDensity(float _ni)
{
    m_niOpticaldensity = _ni;
}

inline void Material::setEmissiveCoeficient(const glm::vec3& _ke)
{
    m_Ke = _ke;
}

}

