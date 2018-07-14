#pragma once

#include <glm/glm.hpp>

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

    const std::string& getName() const;
    const glm::vec3& getAmbient() const;
    const glm::vec3& getDiffuse() const;
    const glm::vec3& getSpecular() const;
    const glm::vec3& getTransmissionFilter() const;
    int getIllumination() const;
    float getDissolve() const;
    bool getHalo() const;
    float getSpecularExponent() const;
    float getSharpness() const;
    float getopticalDensity() const;
    Map* getKamap() const;
    Map* getKdmap() const;
    Map* getKsmap() const;
    Map* getNsmap() const;
    Map* getdmap() const;
    Map* getDecalmap() const;
    Map* getDispmap() const;
    Map* getBumpmap() const;

    void setAmbient(const glm::vec3&);
    void setDiffuse(const glm::vec3&);
    void setSpecular(const glm::vec3&);
    void setTransmissionFilter(const glm::vec3&);
    void setIllumination(int);
    void setDissolve(float);
    void setHalo(bool);
    void setSpecularExponent(float);
    void setSharpness(float);
    void setopticalDensity(float);
    void setEmissiveCoeficient(const glm::vec3&);
    void setKamap(const std::string&) throw();
    void setKdmap(const std::string&) throw();
    void setKsmap(const std::string&) throw();
    void setNsmap(const std::string&) throw();
    void setdmap(const std::string&) throw();
    void setDecalmap(const std::string&) throw();
    void setDispmap(const std::string&) throw();
    void setBumpmap(const std::string&) throw();

    std::ostream& print(std::ostream&) const;

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

std::ostream& operator<<(std::ostream&, const Material&);

}

