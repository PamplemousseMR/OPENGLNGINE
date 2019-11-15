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

class Map
{

public:

    enum MAP_TYPE
    {
        KA,
        KD,
        KS,
        NS,
        D,
        DECAL,
        DISP,
        BUMP
    };

public:

    Map(MAP_TYPE, const std::filesystem::path&);
    ~Map();
    Map(const Map&);
    Map(Map&&);
    Map& operator=(const Map&);
    Map& operator=(Map&&);

    GL::Texture& getTexture() const;
    inline const std::string& getName() const;
    inline bool getBlendu() const;
    inline bool getBlendv() const;
    bool getCc() const;
    bool getClamp() const;
    inline const glm::vec3& getImfchanrgb() const;
    inline const glm::vec3& getImfchanmlz() const;
    inline float getBase() const;
    inline float getGain() const;
    inline const glm::vec3& getO() const;
    inline const glm::vec3& getS() const;
    inline const glm::vec3& getT() const;
    inline int getTextres() const;
    inline float getMult() const;
    inline float getBoost() const;
    inline float getMapaat() const;

    inline void setBlendu(bool);
    inline void setBlendv(bool);
    void setCc(bool);
    void setClamp(bool);
    inline void setImfchanrgb(const glm::vec3&);
    inline void setImfchanmlz(const glm::vec3&);
    inline void setBase(float);
    inline void setGain(float);
    inline void setO(const glm::vec3&);
    inline void setS(const glm::vec3&);
    inline void setT(const glm::vec3&);
    inline void setTextres(int);
    inline void setMult(float);
    inline void setBoost(float);
    inline void setMapaat(bool);

    std::ostream& print(std::ostream&) const;

private:

    std::string m_name {};
    MAP_TYPE m_mapType {};
    GL::Texture* m_texture {};
    bool m_blendu {true};
    bool m_blendv {true};
    bool m_cc {false};
    bool m_clamp {false};
    glm::vec3 m_imfchanrgb {0, 0, 0};
    glm::vec3 m_imfchanmlz {0, 0, 0};
    float m_base {0};
    float m_gain {1};
    glm::vec3 m_o {0, 0, 0};
    glm::vec3 m_s {1, 1, 1};
    glm::vec3 m_t {0, 0, 0};
    int m_textres {0};
    float m_mult {1};
    float m_boost {1};
    bool m_mapAat {true};

};

std::ostream& operator<<(std::ostream&, const Map&);

inline const std::string& Map::getName() const
{
    return m_name;
}

inline void Map::setBlendu(bool _blendu)
{
    m_blendu = _blendu;
}

inline void Map::setBlendv(bool _blendv)
{
    m_blendv = _blendv;
}

inline void Map::setImfchanrgb(const glm::vec3& _rgb)
{
    m_imfchanrgb = _rgb;
}

inline void Map::setImfchanmlz(const glm::vec3& _mlz)
{
    m_imfchanmlz = _mlz;
}

inline void Map::setBase(float _base)
{
    m_base = _base;
}

inline void Map::setGain(float _gain)
{
    m_gain = _gain;
}

inline void Map::setO(const glm::vec3& _o)
{
    m_o = _o;
}

inline void Map::setS(const glm::vec3& _s)
{
    m_s = _s;
}

inline void Map::setT(const glm::vec3& _t)
{
    m_t = _t;
}

inline void Map::setTextres(int _textres)
{
    m_textres = _textres;
}

inline void Map::setMult(float _mult)
{
    m_mult = _mult;
}

inline void Map::setBoost(float _boost)
{
    m_boost = _boost;
}

inline void Map::setMapaat(bool _aat)
{
    m_mapAat = _aat;
}

inline bool Map::getBlendu() const
{
    return m_blendu;
}

inline bool Map::getBlendv() const
{
    return m_blendv;
}

inline const glm::vec3& Map::getImfchanrgb() const
{
    return m_imfchanrgb;
}

inline const glm::vec3& Map::getImfchanmlz() const
{
    return m_imfchanmlz;
}

inline float Map::getBase() const
{
    return m_base;
}

inline float Map::getGain() const
{
    return m_gain;
}

inline const glm::vec3& Map::getO() const
{
    return m_o;
}

inline const glm::vec3& Map::getS() const
{
    return m_s;
}

inline const glm::vec3& Map::getT() const
{
    return m_t;
}

inline int Map::getTextres() const
{
    return m_textres;
}

inline float Map::getMult() const
{
    return m_mult;
}

inline float Map::getBoost() const
{
    return m_boost;
}

inline float Map::getMapaat() const
{
    return m_mapAat;
}

}


