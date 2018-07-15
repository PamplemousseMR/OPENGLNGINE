#include "Asset/Map.hpp"
#include "GL/Texture.hpp"

using namespace glm;
using namespace std;
using namespace GL;

namespace Assets
{

    Map::Map(MAP_TYPE _mapType, const std::filesystem::path& _path) :
        m_name(_path.filename().string()),
        m_mapType(_mapType)
    {
        m_texture = new Texture(Texture::TEXTURE_2D);
        m_texture->bind();
        try
        {
            m_textres = m_texture->load(_path);
        }
        catch (const exception& _e)
        {
            throw invalid_argument("[Map] " + string(_e.what()));
        }
        m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        m_texture->generateMipmap();
        m_texture->unbind();
    }

    Map::~Map() noexcept
    {
        delete m_texture;
    }

    ostream& Map::print(ostream& _o) const noexcept
    {
        _o << "[Map " << m_name << "] " << m_mapType << "\n";
        _o << "\t" << "blendu " << m_blendu << "\n";
        _o << "\t" << "blendv " << m_blendv << "\n";
        _o << "\t" << "cc " << m_cc << "\n";
        _o << "\t" << "clamp " << m_clamp << "\n";
        _o << "\t" << "imfchang " << m_imfchanrgb[0] << " " << m_imfchanrgb[1] << " " << m_imfchanrgb[2] << " " << m_imfchanmlz[0] << " " << m_imfchanmlz[1] << " " << m_imfchanmlz[2] << "\n";
        _o << "\t" << "base " << m_base << "\n";
        _o << "\t" << "gain " << m_gain << "\n";
        _o << "\t" << "p " << m_o[0] << " " << m_o[1] << " " << m_o[2] << "\n";
        _o << "\t" << "s " << m_s[0] << " " << m_s[1] << " " << m_s[2] << "\n";
        _o << "\t" << "t " << m_t[0] << " " << m_t[1] << " " << m_t[2] << "\n";
        _o << "\t" << "mult " << m_mult << "\n";
        _o << "\t" << "boost " << m_boost << "\n";
        _o << "\t" << "map_aat " << m_mapAat << "\n";
        return _o;
    }

    const string& Map::getName() const noexcept
    {
        return m_name;
    }

    void Map::setBlendu(bool _blendu) noexcept
    {
        m_blendu = _blendu;
    }

    void Map::setBlendv(bool _blendv) noexcept
    {
        m_blendv = _blendv;
    }

    void Map::setCc(bool _cc)
    {
        if (m_mapType == KA || m_mapType == KD || m_mapType == KS)
        {
            m_cc = _cc;
        }
        else
        {
            throw invalid_argument("[Map] can't set cc for this mapType");
        }
    }

    void Map::setClamp(bool _clamp)
    {
        if (m_mapType == NS || m_mapType == D || m_mapType == DECAL || m_mapType == DISP)
        {
            m_clamp = _clamp;
        }
        else
        {
            throw invalid_argument("[Map] can't set clamp for this mapType");
        }
    }

    void Map::setImfchanrgb(const vec3& _rgb) noexcept
    {
        m_imfchanrgb = _rgb;
    }

    void Map::setImfchanmlz(const vec3& _mlz) noexcept
    {
        m_imfchanmlz = _mlz;
    }

    void Map::setBase(float _base) noexcept
    {
        m_base = _base;
    }

    void Map::setGain(float _gain) noexcept
    {
        m_gain = _gain;
    }

    void Map::setO(const vec3& _o) noexcept
    {
        m_o = _o;
    }

    void Map::setS(const vec3& _s) noexcept
    {
        m_s = _s;
    }

    void Map::setT(const vec3& _t) noexcept
    {
        m_t = _t;
    }

    void Map::setTextres(int _textres) noexcept
    {
        m_textres = _textres;
    }

    void Map::setMult(float _mult) noexcept
    {
        m_mult = _mult;
    }

    void Map::setBoost(float _boost) noexcept
    {
        m_boost = _boost;
    }

    void Map::setMapaat(bool _aat) noexcept
    {
        m_mapAat = _aat;
    }

    Texture* Map::getTexture() const noexcept
    {
        return m_texture;
    }

    bool Map::getBlendu() const noexcept
    {
        return m_blendu;
    }

    bool Map::getBlendv() const noexcept
    {
        return m_blendv;
    }

    bool Map::getCc() const
    {
        if (m_mapType == KA || m_mapType == KD || m_mapType == KS)
        {
            return m_cc;
        }
        else
        {
            throw invalid_argument("[Map " + m_name + "] [getCc() const throw()] can't get cc for this mapType");
        }
    }

    bool Map::getClamp() const
    {
        if (m_mapType == NS || m_mapType == D || m_mapType == DECAL || m_mapType == DISP)
        {
            return m_clamp;
        }
        else
        {
            throw invalid_argument("[Map " + m_name + "] [getClamp() const throw()] can't get clamp for this mapType");
        }
    }

    const vec3& Map::getImfchanrgb() const noexcept
    {
        return m_imfchanrgb;
    }

    const vec3& Map::getImfchanmlz() const noexcept
    {
        return m_imfchanmlz;
    }

    float Map::getBase() const noexcept
    {
        return m_base;
    }

    float Map::getGain() const noexcept
    {
        return m_gain;
    }

    const vec3& Map::getO() const noexcept
    {
        return m_o;
    }

    const vec3& Map::getS() const noexcept
    {
        return m_s;
    }

    const vec3& Map::getT() const noexcept
    {
        return m_t;
    }

    int Map::getTextres() const noexcept
    {
        return m_textres;
    }

    float Map::getMult() const noexcept
    {
        return m_mult;
    }

    float Map::getBoost() const noexcept
    {
        return m_boost;
    }

    float Map::getMapaat() const noexcept
    {
        return m_mapAat;
    }

    ostream& operator<<(ostream& _o, const Map& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
