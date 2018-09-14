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
    Map *m_kaMap {nullptr};
    Map *m_kdMap {nullptr};
    Map* m_ksMap {nullptr};
    Map* m_nsMap {nullptr};
    Map* m_dMap {nullptr};
    Map* m_dispMap {nullptr};
    Map* m_decalMap {nullptr};
    Map* m_bumpMap {nullptr};

};

std::ostream& operator<<(std::ostream&, const Material&) noexcept;

}

