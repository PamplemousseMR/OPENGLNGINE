#pragma once

#include <glm/glm.hpp>

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

    const std::string& getName() const noexcept;
    const glm::vec3& getAmbient() const noexcept;
    const glm::vec3& getDiffuse() const noexcept;
    const glm::vec3& getSpecular() const noexcept;
    const glm::vec3& getTransmissionFilter() const noexcept;
    int getIllumination() const noexcept;
    float getDissolve() const noexcept;
    bool getHalo() const noexcept;
    float getSpecularExponent() const noexcept;
    float getSharpness() const noexcept;
    float getopticalDensity() const noexcept;
    Map* getKamap() const noexcept;
    Map* getKdmap() const noexcept;
    Map* getKsmap() const noexcept;
    Map* getNsmap() const noexcept;
    Map* getdmap() const noexcept;
    Map* getDecalmap() const noexcept;
    Map* getDispmap() const noexcept;
    Map* getBumpmap() const noexcept;

    void setAmbient(const glm::vec3&) noexcept;
    void setDiffuse(const glm::vec3&) noexcept;
    void setSpecular(const glm::vec3&) noexcept;
    void setTransmissionFilter(const glm::vec3&) noexcept;
    void setIllumination(int) noexcept;
    void setDissolve(float) noexcept;
    void setHalo(bool) noexcept;
    void setSpecularExponent(float) noexcept;
    void setSharpness(float) noexcept;
    void setopticalDensity(float) noexcept;
    void setEmissiveCoeficient(const glm::vec3&) noexcept;
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

    std::string m_name;
    glm::vec3 m_kaAmbient;
    glm::vec3 m_kdDiffuse;
    glm::vec3 m_ksSpecular;
    glm::vec3 m_tfTransmissionfilter;
    int m_illumIllumination;
    float m_dDissolve;
    bool m_halo;
    float m_nsSpecularexponent;
    float m_sharpnessSharpness;
    float m_niOpticaldensity;
    glm::vec3 m_Ke;
    Map *m_kaMap;
    Map *m_kdMap;
    Map* m_ksMap;
    Map* m_nsMap;
    Map* m_dMap;
    Map* m_dispMap;
    Map* m_decalMap;
    Map* m_bumpMap;

};

std::ostream& operator<<(std::ostream&, const Material&) noexcept;

}

