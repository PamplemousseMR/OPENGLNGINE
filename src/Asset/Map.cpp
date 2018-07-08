#include "Asset/Map.h"
#include "GL/Texture.h"

using namespace glm;
using namespace std;
using namespace GL;

namespace Assets
{

    Map::Map(MAP_TYPE mapType, const string& path) throw(...)
        : m_name(path),
        m_mapType(mapType),
        m_blendu(true),
        m_blendv(true),
        m_cc(false),
        m_clamp(false),
        m_imfchanrgb(0, 0, 0),
        m_imfchanmlz(0, 0, 0),
        m_base(0),
        m_gain(1),
        m_o(0, 0, 0),
        m_s(1, 1, 1),
        m_t(0, 0, 0),
        m_mult(1),
        m_boost(1),
        m_mapAat(true)
	{
#ifdef _DEBUG
        cout << "[Map " << m_name << "] [Map(mapType mapType, const tring& path) throw(...)]..." << endl;
#endif
        m_texture = new Texture(textureType::TEXTURE_2D);
        m_texture->bind();
		try {
            m_textres = m_texture->load(path.c_str());
		}
		catch (exception e) {
            throw invalid_argument("[Map " + m_name + "] [Map(mapType mapType, const tring& path) throw(...)] " + e.what());
		}
        m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        m_texture->generateMipmap();
        m_texture->unbind();
#ifdef _DEBUG
        cout << "[Map " << m_name << "] [Map(mapType mapType, const tring& path) throw(...)]...\tsuccess" << endl;
#endif
	}

	Map::~Map()
	{
#ifdef _DEBUG
        cout << "[Map " << m_name << "] [~Map()]..." << endl;
#endif
        delete m_texture;
#ifdef _DEBUG
        cout << "[Map " << m_name << "] [~Map()]...\tsuccess" << endl;
#endif
	}

	ostream& Map::print(ostream& o) const
	{
        o << "[Map " << m_name << "] " << m_mapType << "\n";
        o << "\t" << "blendu " << m_blendu << "\n";
        o << "\t" << "blendv " << m_blendv << "\n";
        o << "\t" << "cc " << m_cc << "\n";
        o << "\t" << "clamp " << m_clamp << "\n";
        o << "\t" << "imfchang " << m_imfchanrgb[0] << " " << m_imfchanrgb[1] << " " << m_imfchanrgb[2] << " " << m_imfchanmlz[0] << " " << m_imfchanmlz[1] << " " << m_imfchanmlz[2] << "\n";
        o << "\t" << "base " << m_base << "\n";
        o << "\t" << "gain " << m_gain << "\n";
        o << "\t" << "p " << m_o[0] << " " << m_o[1] << " " << m_o[2] << "\n";
        o << "\t" << "s " << m_s[0] << " " << m_s[1] << " " << m_s[2] << "\n";
        o << "\t" << "t " << m_t[0] << " " << m_t[1] << " " << m_t[2] << "\n";
        o << "\t" << "mult " << m_mult << "\n";
        o << "\t" << "boost " << m_boost << "\n";
        o << "\t" << "map_aat " << m_mapAat << "\n";
		return o;
	}

	const string& Map::getName() const
	{
        return m_name;
	}

	void Map::setBlendu(bool blendu)
	{
        m_blendu = blendu;
	}

	void Map::setBlendv(bool blendv)
	{
        m_blendv = blendv;
	}

	void Map::setCc(bool cc) throw(...)
	{
        if (m_mapType == Ka || m_mapType == Kd || m_mapType == Ks)
            m_cc = cc;
		else
            throw invalid_argument("[Map " + m_name + "] [setCc(bool cc) throw(...)] can't set cc for this mapType");
	}

	void Map::setClamp(bool clamp) throw(...)
	{
        if (m_mapType == Ns || m_mapType == d || m_mapType == decal || m_mapType == disp)
            m_clamp = clamp;
		else
            throw invalid_argument("[Map " + m_name + "] [setClamp(bool clamp) throw(...)] can't set clamp for this mapType");
	}

	void Map::setImfchanrgb(const vec3& rgb)
	{
        m_imfchanrgb = rgb;
	}

	void Map::setImfchanmlz(const vec3& mlz)
	{
        m_imfchanmlz = mlz;
	}

	void Map::setBase(float base)
	{
        m_base = base;
	}

	void Map::setGain(float gain)
	{
        m_gain = gain;
	}

	void Map::setO(const vec3& o)
	{
        m_o = o;
	}

	void Map::setS(const vec3& s)
	{
        m_s = s;
	}

	void Map::setT(const vec3& t)
	{
        m_t = t;
	}

	void Map::setTextres(int textres)
	{
        m_textres = textres;
	}

	void Map::setMult(float mult)
	{
        m_mult = mult;
	}

	void Map::setBoost(float boost)
	{
        m_boost = boost;
	}

	void Map::setMapaat(bool aat)
	{
        m_mapAat = aat;
	}

	Texture* Map::getTexture() const
	{
        return m_texture;
	}

	bool Map::getBlendu() const
	{
        return m_blendu;
	}

	bool Map::getBlendv() const
	{
        return m_blendv;
	}

	bool Map::getCc() const throw(...)
	{
        if (m_mapType == Ka || m_mapType == Kd || m_mapType == Ks)
            return m_cc;
		else
            throw invalid_argument("[Map " + m_name + "] [getCc() const throw(...)] can't get cc for this mapType");
	}

	bool Map::getClamp() const throw(...)
	{
        if (m_mapType == Ns || m_mapType == d || m_mapType == decal || m_mapType == disp)
            return m_clamp;
		else
            throw invalid_argument("[Map " + m_name + "] [getClamp() const throw(...)] can't get clamp for this mapType");
	}

	const vec3& Map::getImfchanrgb() const
	{
        return m_imfchanrgb;
	}

	const vec3& Map::getImfchanmlz() const
	{
        return m_imfchanmlz;
	}

	float Map::getBase() const
	{
        return m_base;
	}

	float Map::getGain() const
	{
        return m_gain;
	}

	const vec3& Map::getO() const
	{
        return m_o;
	}

	const vec3& Map::getS() const
	{
        return m_s;
	}

	const vec3& Map::getT() const
	{
        return m_t;
	}

	int Map::getTextres() const
	{
        return m_textres;
	}

	float Map::getMult() const
	{
        return m_mult;
	}

	float Map::getBoost() const
	{
        return m_boost;
	}

	float Map::getMapaat() const
	{
        return m_mapAat;
	}

	ostream& operator<<(ostream& o, const Map& m)
	{
		m.print(o);
		return o;
	}
}
