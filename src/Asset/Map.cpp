#include "Asset/Map.h"
#include "GL/Texture.h"

using namespace glm;
using namespace std;
using namespace GL;

namespace Assets
{

	Map::Map(mapType mapType, const string& path) throw(...)
		: _name(path),
		_mapType(mapType),
		_blendu(true),
		_blendv(true),
		_cc(false),
		_clamp(false),
		_imfchanrgb(0, 0, 0),
		_imfchanmlz(0, 0, 0),
		_base(0),
		_gain(1),
		_o(0, 0, 0),
		_s(1, 1, 1),
		_t(0, 0, 0),
		_mult(1),
		_boost(1),
		_map_aat(true)
	{
#ifdef _DEBUG
		cout << "[Map " << _name << "] [Map(mapType mapType, const tring& path) throw(...)]..." << endl;
#endif
		_texture = new Texture(textureType::TEXTURE_2D);
		_texture->bind();
		try {
			_textres = _texture->load(path.c_str());
		}
		catch (exception e) {
			throw invalid_argument("[Map " + _name + "] [Map(mapType mapType, const tring& path) throw(...)] " + e.what());
		}
		_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		_texture->generateMipmap();
		_texture->unbind();
#ifdef _DEBUG
		cout << "[Map " << _name << "] [Map(mapType mapType, const tring& path) throw(...)]...\tsuccess" << endl;
#endif
	}

	Map::~Map()
	{
#ifdef _DEBUG
		cout << "[Map " << _name << "] [~Map()]..." << endl;
#endif
		delete _texture;
#ifdef _DEBUG
		cout << "[Map " << _name << "] [~Map()]...\tsuccess" << endl;
#endif
	}

	ostream& Map::print(ostream& o) const
	{
		o << "[Map " << _name << "] " << _mapType << "\n";
		o << "\t" << "blendu " << _blendu << "\n";
		o << "\t" << "blendv " << _blendv << "\n";
		o << "\t" << "cc " << _cc << "\n";
		o << "\t" << "clamp " << _clamp << "\n";
		o << "\t" << "imfchang " << _imfchanrgb[0] << " " << _imfchanrgb[1] << " " << _imfchanrgb[2] << " " << _imfchanmlz[0] << " " << _imfchanmlz[1] << " " << _imfchanmlz[2] << "\n";
		o << "\t" << "base " << _base << "\n";
		o << "\t" << "gain " << _gain << "\n";
		o << "\t" << "p " << _o[0] << " " << _o[1] << " " << _o[2] << "\n";
		o << "\t" << "s " << _s[0] << " " << _s[1] << " " << _s[2] << "\n";
		o << "\t" << "t " << _t[0] << " " << _t[1] << " " << _t[2] << "\n";
		o << "\t" << "mult " << _mult << "\n";
		o << "\t" << "boost " << _boost << "\n";
		o << "\t" << "map_aat " << _map_aat << "\n";
		return o;
	}

	const string& Map::getName() const
	{
		return _name;
	}

	void Map::setBlendu(bool blendu)
	{
		_blendu = blendu;
	}

	void Map::setBlendv(bool blendv)
	{
		_blendv = blendv;
	}

	void Map::setCc(bool cc) throw(...)
	{
		if (_mapType == Ka || _mapType == Kd || _mapType == Ks)
			_cc = cc;
		else
			throw invalid_argument("[Map " + _name + "] [setCc(bool cc) throw(...)] can't set cc for this mapType");
	}

	void Map::setClamp(bool clamp) throw(...)
	{
		if (_mapType == Ns || _mapType == d || _mapType == decal || _mapType == disp)
			_clamp = clamp;
		else
			throw invalid_argument("[Map " + _name + "] [setClamp(bool clamp) throw(...)] can't set clamp for this mapType");
	}

	void Map::setImfchanrgb(const vec3& rgb)
	{
		_imfchanrgb = rgb;
	}

	void Map::setImfchanmlz(const vec3& mlz)
	{
		_imfchanmlz = mlz;
	}

	void Map::setBase(float base)
	{
		_base = base;
	}

	void Map::setGain(float gain)
	{
		_gain = gain;
	}

	void Map::setO(const vec3& o)
	{
		_o = o;
	}

	void Map::setS(const vec3& s)
	{
		_s = s;
	}

	void Map::setT(const vec3& t)
	{
		_t = t;
	}

	void Map::setTextres(int textres)
	{
		_textres = textres;
	}

	void Map::setMult(float mult)
	{
		_mult = mult;
	}

	void Map::setBoost(float boost)
	{
		_boost = boost;
	}

	void Map::setMapaat(bool aat)
	{
		_map_aat = aat;
	}

	Texture* Map::getTexture() const
	{
		return _texture;
	}

	bool Map::getBlendu() const
	{
		return _blendu;
	}

	bool Map::getBlendv() const
	{
		return _blendv;
	}

	bool Map::getCc() const throw(...)
	{
		if (_mapType == Ka || _mapType == Kd || _mapType == Ks)
			return _cc;
		else
			throw invalid_argument("[Map " + _name + "] [getCc() const throw(...)] can't get cc for this mapType");
	}

	bool Map::getClamp() const throw(...)
	{
		if (_mapType == Ns || _mapType == d || _mapType == decal || _mapType == disp)
			return _clamp;
		else
			throw invalid_argument("[Map " + _name + "] [getClamp() const throw(...)] can't get clamp for this mapType");
	}

	const vec3& Map::getImfchanrgb() const
	{
		return _imfchanrgb;
	}

	const vec3& Map::getImfchanmlz() const
	{
		return _imfchanmlz;
	}

	float Map::getBase() const
	{
		return _base;
	}

	float Map::getGain() const
	{
		return _gain;
	}

	const vec3& Map::getO() const
	{
		return _o;
	}

	const vec3& Map::getS() const
	{
		return _s;
	}

	const vec3& Map::getT() const
	{
		return _t;
	}

	int Map::getTextres() const
	{
		return _textres;
	}

	float Map::getMult() const
	{
		return _mult;
	}

	float Map::getBoost() const
	{
		return _boost;
	}

	float Map::getMapaat() const
	{
		return _map_aat;
	}

	ostream& operator<<(ostream& o, const Map& m)
	{
		m.print(o);
		return o;
	}
}
