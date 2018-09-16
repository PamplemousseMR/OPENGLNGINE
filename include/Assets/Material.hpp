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

    Material(const std::string&) noexcept;
    ~Material() noexcept;
    Material(const Material&);
    Material(Material&&);
    Material& operator=(const Material&);
    Material& operator=(Material&&);

    inline const std::string& getName() const noexcept;
    inline const glm::vec3& getAmbient() const noexcept;
    inline const glm::vec3& getDiffuse() const noexcept;
    inline const glm::vec3& getSpecular() const noexcept;
    inline const glm::vec3& getTransmissionFilter() const noexcept;
    inline int getIllumination() const noexcept;
    inline float getDissolve() const noexcept;
    inline bool getHalo() const noexcept;
    inline float getSpecularExponent() const noexcept;
    inline float getSharpness() const noexcept;
    inline float getopticalDensity() const noexcept;
    Map* getKamap() const noexcept;
    Map* getKdmap() const noexcept;
    Map* getKsmap() const noexcept;
    Map* getNsmap() const noexcept;
    Map* getdmap() const noexcept;
    Map* getDecalmap() const noexcept;
    Map* getDispmap() const noexcept;
    Map* getBumpmap() const noexcept;

    inline void setAmbient(const glm::vec3&) noexcept;
    inline void setDiffuse(const glm::vec3&) noexcept;
    inline void setSpecular(const glm::vec3&) noexcept;
    inline void setTransmissionFilter(const glm::vec3&) noexcept;
    inline void setIllumination(int) noexcept;
    inline void setDissolve(float) noexcept;
    inline void setHalo(bool) noexcept;
    inline void setSpecularExponent(float) noexcept;
    inline void setSharpness(float) noexcept;
    inline void setopticalDensity(float) noexcept;
    inline void setEmissiveCoeficient(const glm::vec3&) noexcept;
    void setKamap(const std::filesystem::path&);
    void setKdmap(const std::filesystem::path&);
    void setKsmap(const std::filesystem::path&);
    void setNsmap(const std::filesystem::path&);
    void setdmap(const std::filesystem::path&);
    void setDecalmap(const std::filesystem::path&);
    void setDispmap(const std::filesystem::path&);
    void setBumpmap(const std::filesystem::path&);

    std::ostream& print(std::ostream&) const noexcept;

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

std::ostream& operator<<(std::ostream&, const Material&) noexcept;

inline const std::string& Material::getName() const noexcept
{
    return m_name;
}

inline const glm::vec3& Material::getAmbient() const noexcept
{
    return m_kaAmbient;
}

inline const glm::vec3& Material::getDiffuse() const noexcept
{
    return m_kdDiffuse;
}

inline const glm::vec3& Material::getSpecular() const noexcept
{
    return m_ksSpecular;
}

inline const glm::vec3& Material::getTransmissionFilter() const noexcept
{
    return m_tfTransmissionfilter;
}

inline int Material::getIllumination() const noexcept
{
    return m_illumIllumination;
}

inline float Material::getDissolve() const noexcept
{
    return m_dDissolve;
}

inline bool Material::getHalo() const noexcept
{
    return m_halo;
}

inline float Material::getSpecularExponent() const noexcept
{
    return m_nsSpecularexponent;
}

inline float Material::getSharpness() const noexcept
{
    return m_sharpnessSharpness;
}

inline float Material::getopticalDensity() const noexcept
{
    return m_niOpticaldensity;
}

inline void Material::setAmbient(const glm::vec3& _ka) noexcept
{
    m_kaAmbient = _ka;
}

inline void Material::setDiffuse(const glm::vec3& _kd) noexcept
{
    m_kdDiffuse = _kd;
}

inline void Material::setSpecular(const glm::vec3& _ks) noexcept
{
    m_ksSpecular = _ks;
}

inline void Material::setTransmissionFilter(const glm::vec3& _tf) noexcept
{
    m_tfTransmissionfilter = _tf;
}

inline void Material::setIllumination(int _illum) noexcept
{
    m_illumIllumination = _illum;
}

inline void Material::setDissolve(float _d) noexcept
{
    m_dDissolve = _d;
}

inline void Material::setHalo(bool _h) noexcept
{
    m_halo = _h;
}

inline void Material::setSpecularExponent(float _ns) noexcept
{
    m_nsSpecularexponent = _ns;
}

inline void Material::setSharpness(float _sharp) noexcept
{
    m_sharpnessSharpness = _sharp;
}

inline void Material::setopticalDensity(float _ni) noexcept
{
    m_niOpticaldensity = _ni;
}

inline void Material::setEmissiveCoeficient(const glm::vec3& _ke) noexcept
{
    m_Ke = _ke;
}

}

