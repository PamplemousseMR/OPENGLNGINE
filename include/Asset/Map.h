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

enum MAP_TYPE
{
    Ka,
    Kd,
    Ks,
    Ns,
    d,
    decal,
    disp,
    bump
};

class Map
{

public:

	Map(MAP_TYPE, const std::string&) throw();
    ~Map();

    GL::Texture* getTexture() const;
    const std::string& getName() const;
    bool getBlendu() const;
    bool getBlendv() const;
	bool getCc() const throw();
	bool getClamp() const throw();
    const glm::vec3& getImfchanrgb() const;
    const glm::vec3& getImfchanmlz() const;
    float getBase() const;
    float getGain() const;
    const glm::vec3& getO() const;
    const glm::vec3& getS() const;
    const glm::vec3& getT() const;
    int getTextres() const;
    float getMult() const;
    float getBoost() const;
    float getMapaat() const;

    void setBlendu(bool);
    void setBlendv(bool);
	void setCc(bool) throw();
	void setClamp(bool) throw();
    void setImfchanrgb(const glm::vec3&);
    void setImfchanmlz(const glm::vec3&);
    void setBase(float);
    void setGain(float);
    void setO(const glm::vec3&);
    void setS(const glm::vec3&);
    void setT(const glm::vec3&);
    void setTextres(int);
    void setMult(float);
    void setBoost(float);
    void setMapaat(bool);

    std::ostream& print(std::ostream&) const;

private:

    std::string m_name;
    MAP_TYPE m_mapType;
    GL::Texture* m_texture;
    bool m_blendu;
    bool m_blendv;
    bool m_cc;
    bool m_clamp;
    glm::vec3 m_imfchanrgb;
    glm::vec3 m_imfchanmlz;
    float m_base;
    float m_gain;
    glm::vec3 m_o;
    glm::vec3 m_s;
    glm::vec3 m_t;
    int m_textres;
    float m_mult;
    float m_boost;
    bool m_mapAat;

};

std::ostream& operator<<(std::ostream&, const Map&);

}


