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

    GL::Texture* getTexture() const noexcept;
    const std::string& getName() const noexcept;
    bool getBlendu() const noexcept;
    bool getBlendv() const noexcept;
    bool getCc() const;
    bool getClamp() const;
    const glm::vec3& getImfchanrgb() const noexcept;
    const glm::vec3& getImfchanmlz() const noexcept;
    float getBase() const noexcept;
    float getGain() const noexcept;
    const glm::vec3& getO() const noexcept;
    const glm::vec3& getS() const noexcept;
    const glm::vec3& getT() const noexcept;
    int getTextres() const noexcept;
    float getMult() const noexcept;
    float getBoost() const noexcept;
    float getMapaat() const noexcept;

    void setBlendu(bool) noexcept;
    void setBlendv(bool) noexcept;
    void setCc(bool);
    void setClamp(bool);
    void setImfchanrgb(const glm::vec3&) noexcept;
    void setImfchanmlz(const glm::vec3&) noexcept;
    void setBase(float) noexcept;
    void setGain(float) noexcept;
    void setO(const glm::vec3&) noexcept;
    void setS(const glm::vec3&) noexcept;
    void setT(const glm::vec3&) noexcept;
    void setTextres(int) noexcept;
    void setMult(float) noexcept;
    void setBoost(float) noexcept;
    void setMapaat(bool) noexcept;

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

}


