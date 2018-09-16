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
    ~Map() noexcept;
    Map(const Map&);
    Map& operator=(const Map&);

    GL::Texture* getTexture() const noexcept;
    inline const std::string& getName() const noexcept;
    inline bool getBlendu() const noexcept;
    inline bool getBlendv() const noexcept;
    bool getCc() const;
    bool getClamp() const;
    inline const glm::vec3& getImfchanrgb() const noexcept;
    inline const glm::vec3& getImfchanmlz() const noexcept;
    inline float getBase() const noexcept;
    inline float getGain() const noexcept;
    inline const glm::vec3& getO() const noexcept;
    inline const glm::vec3& getS() const noexcept;
    inline const glm::vec3& getT() const noexcept;
    inline int getTextres() const noexcept;
    inline float getMult() const noexcept;
    inline float getBoost() const noexcept;
    inline float getMapaat() const noexcept;

    inline void setBlendu(bool) noexcept;
    inline void setBlendv(bool) noexcept;
    void setCc(bool);
    void setClamp(bool);
    inline void setImfchanrgb(const glm::vec3&) noexcept;
    inline void setImfchanmlz(const glm::vec3&) noexcept;
    inline void setBase(float) noexcept;
    inline void setGain(float) noexcept;
    inline void setO(const glm::vec3&) noexcept;
    inline void setS(const glm::vec3&) noexcept;
    inline void setT(const glm::vec3&) noexcept;
    inline void setTextres(int) noexcept;
    inline void setMult(float) noexcept;
    inline void setBoost(float) noexcept;
    inline void setMapaat(bool) noexcept;

    std::ostream& print(std::ostream&) const noexcept;

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

std::ostream& operator<<(std::ostream&, const Map&) noexcept;

inline const std::string& Map::getName() const noexcept
{
    return m_name;
}

inline void Map::setBlendu(bool _blendu) noexcept
{
    m_blendu = _blendu;
}

inline void Map::setBlendv(bool _blendv) noexcept
{
    m_blendv = _blendv;
}

inline void Map::setImfchanrgb(const glm::vec3& _rgb) noexcept
{
    m_imfchanrgb = _rgb;
}

inline void Map::setImfchanmlz(const glm::vec3& _mlz) noexcept
{
    m_imfchanmlz = _mlz;
}

inline void Map::setBase(float _base) noexcept
{
    m_base = _base;
}

inline void Map::setGain(float _gain) noexcept
{
    m_gain = _gain;
}

inline void Map::setO(const glm::vec3& _o) noexcept
{
    m_o = _o;
}

inline void Map::setS(const glm::vec3& _s) noexcept
{
    m_s = _s;
}

inline void Map::setT(const glm::vec3& _t) noexcept
{
    m_t = _t;
}

inline void Map::setTextres(int _textres) noexcept
{
    m_textres = _textres;
}

inline void Map::setMult(float _mult) noexcept
{
    m_mult = _mult;
}

inline void Map::setBoost(float _boost) noexcept
{
    m_boost = _boost;
}

inline void Map::setMapaat(bool _aat) noexcept
{
    m_mapAat = _aat;
}

inline bool Map::getBlendu() const noexcept
{
    return m_blendu;
}

inline bool Map::getBlendv() const noexcept
{
    return m_blendv;
}

inline const glm::vec3& Map::getImfchanrgb() const noexcept
{
    return m_imfchanrgb;
}

inline const glm::vec3& Map::getImfchanmlz() const noexcept
{
    return m_imfchanmlz;
}

inline float Map::getBase() const noexcept
{
    return m_base;
}

inline float Map::getGain() const noexcept
{
    return m_gain;
}

inline const glm::vec3& Map::getO() const noexcept
{
    return m_o;
}

inline const glm::vec3& Map::getS() const noexcept
{
    return m_s;
}

inline const glm::vec3& Map::getT() const noexcept
{
    return m_t;
}

inline int Map::getTextres() const noexcept
{
    return m_textres;
}

inline float Map::getMult() const noexcept
{
    return m_mult;
}

inline float Map::getBoost() const noexcept
{
    return m_boost;
}

inline float Map::getMapaat() const noexcept
{
    return m_mapAat;
}

}


