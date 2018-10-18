#include "Assets/Map.hpp"
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
        m_texture = new Texture(Texture::TYPE_2D);
        m_texture->bind();
        m_textres = m_texture->load(_path, Texture::INTERNALFORMAT_RGBA);
        m_texture->setMagFilter(Texture::FILTER_LINEAR);
        m_texture->setMinFilter(Texture::FILTER_LINEAR_MIPMAP_LINEAR);
        m_texture->generateMipmap();
        m_texture->unbind();
    }

    Map::~Map() noexcept
    {
        delete m_texture;
    }

    Map::Map(const Map& _map) :
        m_name(_map.m_name),
        m_mapType(_map.m_mapType),
        m_texture(new Texture(*_map.m_texture)),
        m_blendu(_map.m_blendu),
        m_blendv(_map.m_blendv),
        m_cc(_map.m_cc),
        m_clamp(_map.m_clamp),
        m_imfchanrgb(_map.m_imfchanrgb),
        m_imfchanmlz(_map.m_imfchanmlz),
        m_base(_map.m_base),
        m_gain(_map.m_gain),
        m_o(_map.m_o),
        m_s(_map.m_s),
        m_t(_map.m_t),
        m_textres(_map.m_textres),
        m_mult(_map.m_mult),
        m_boost(_map.m_boost),
        m_mapAat(_map.m_mapAat)
    {
        m_texture->bind();
        m_texture->setMagFilter(Texture::FILTER_LINEAR);
        m_texture->setMinFilter(Texture::FILTER_LINEAR_MIPMAP_LINEAR);
        m_texture->generateMipmap();
        m_texture->unbind();
    }

    Map::Map(Map&& _map) :
        m_name(move(_map.m_name)),
        m_mapType(move(_map.m_mapType)),
        m_blendu(move(_map.m_blendu)),
        m_blendv(move(_map.m_blendv)),
        m_cc(move(_map.m_cc)),
        m_clamp(move(_map.m_clamp)),
        m_imfchanrgb(move(_map.m_imfchanrgb)),
        m_imfchanmlz(move(_map.m_imfchanmlz)),
        m_base(move(_map.m_base)),
        m_gain(move(_map.m_gain)),
        m_o(move(_map.m_o)),
        m_s(move(_map.m_s)),
        m_t(move(_map.m_t)),
        m_textres(move(_map.m_textres)),
        m_mult(move(_map.m_mult)),
        m_boost(move(_map.m_boost)),
        m_mapAat(move(_map.m_mapAat))
    {
        m_texture = _map.m_texture;
        _map.m_texture = nullptr;
    }

    Map& Map::operator=(const Map& _map)
    {
        if(this != &_map)
        {
            delete m_texture;
            m_name = _map.m_name;
            m_mapType = _map.m_mapType;
            m_texture = new Texture(*_map.m_texture);
            m_blendu = _map.m_blendu;
            m_blendv = _map.m_blendv;
            m_cc = _map.m_cc;
            m_clamp = _map.m_clamp;
            m_imfchanrgb = _map.m_imfchanrgb;
            m_imfchanmlz = _map.m_imfchanmlz;
            m_base = _map.m_base;
            m_gain = _map.m_gain;
            m_o = _map.m_o;
            m_s = _map.m_s;
            m_t = _map.m_t;
            m_textres = _map.m_textres;
            m_mult = _map.m_mult;
            m_boost = _map.m_boost;
            m_mapAat = _map.m_mapAat;
            m_texture->bind();
            m_texture->setMagFilter(Texture::FILTER_LINEAR);
            m_texture->setMinFilter(Texture::FILTER_LINEAR_MIPMAP_LINEAR);
            m_texture->generateMipmap();
            m_texture->unbind();
        }
        return *this;
    }

    Map& Map::operator=(Map&& _map)
    {
        if(this != &_map)
        {
            delete m_texture;

            m_name = move(_map.m_name);
            m_mapType = move(_map.m_mapType);
            m_blendu = move(_map.m_blendu);
            m_blendv = move(_map.m_blendv);
            m_cc = move(_map.m_cc);
            m_clamp = move(_map.m_clamp);
            m_imfchanrgb = move(_map.m_imfchanrgb);
            m_imfchanmlz = move(_map.m_imfchanmlz);
            m_base = move(_map.m_base);
            m_gain = move(_map.m_gain);
            m_o = move(_map.m_o);
            m_s = move(_map.m_s);
            m_t = move(_map.m_t);
            m_textres = move(_map.m_textres);
            m_mult = move(_map.m_mult);
            m_boost = move(_map.m_boost);
            m_mapAat = move(_map.m_mapAat);
            m_texture = _map.m_texture;
            _map.m_texture = nullptr;
        }
        return *this;
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

    Texture* Map::getTexture() const noexcept
    {
        return m_texture;
    }

    void Map::setCc(bool _cc)
    {
        if (m_mapType == KA || m_mapType == KD || m_mapType == KS)
        {
            m_cc = _cc;
        }
        else
        {
            throw invalid_argument("[Map] Can't set cc for this mapType");
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
            throw invalid_argument("[Map] Can't set clamp for this mapType");
        }
    }

    bool Map::getCc() const
    {
        if (m_mapType == KA || m_mapType == KD || m_mapType == KS)
        {
            return m_cc;
        }
        else
        {
            throw invalid_argument("[Map " + m_name + "] Can't get cc for this mapType");
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
            throw invalid_argument("[Map " + m_name + "] Can't get clamp for this mapType");
        }
    }

    ostream& operator<<(ostream& _o, const Map& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }
}
