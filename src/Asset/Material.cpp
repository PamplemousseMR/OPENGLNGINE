#include "Asset/Material.h"
#include "Asset/Map.h"

using namespace std;
using namespace glm;

namespace Assets
{
	Material::Material(const string& name)
		: _name(name),
		_NS_specularExponent(90.0f),
		_Ka_ambient(1, 1, 1),
		_Kd_diffuse(1, 1, 1),
		_Ks_specular(1, 1, 1),
		_Tf_transmissionFilter(1, 1, 1),
		_Ni_opticalDensity(1.0f),
		_Ke(0, 0, 0),
		_d_dissolve(1.0f),
		_halo(false),
		_illum_illumination(2),
		_sharpness_sharpness(60.0f),
		_Ka_map(nullptr),
		_Kd_map(nullptr),
		_Ks_map(nullptr),
		_Ns_map(nullptr),
		_d_map(nullptr),
		_disp_map(nullptr),
		_decal_map(nullptr),
		_bump_map(nullptr)
	{
#ifdef _DEBUG
		cout << "[Material " << _name << "] [Material(const string& name)]..." << endl;
		cout << "[Material " << _name << "] [Material(const string& name)]...\tsuccess" << endl;
#endif
	}


	Material::~Material()
	{
#ifdef _DEBUG
		cout << "[Material " << _name << "] [~Material()]..." << endl;
#endif
		if (_Ka_map)delete _Ka_map;
		if (_Kd_map)delete _Kd_map;
		if (_Ks_map)delete _Ks_map;
		if (_Ns_map)delete _Ns_map;
		if (_d_map)delete _d_map;
		if (_disp_map)delete _disp_map;
		if (_decal_map)delete _decal_map;
		if (_bump_map)delete _bump_map;
#ifdef _DEBUG
		cout << "[Material " << _name << "] [~Material()]...\tsuccess" << endl;
#endif
	}

	ostream& Material::print(ostream& o) const
	{
		o << "[Material " << _name << "]\n";
		o << "\tMaterial color & illumination statements :\n";
		o << "\t\tKa " << _Ka_ambient[0] << " " << _Ka_ambient[1] << " " << _Ka_ambient[2] << "\n";
		o << "\t\tKd " << _Kd_diffuse[0] << " " << _Kd_diffuse[1] << " " << _Kd_diffuse[2] << "\n";
		o << "\t\tKs " << _Ks_specular[0] << " " << _Ks_specular[1] << " " << _Ks_specular[2] << "\n";
		o << "\t\tTf " << _Tf_transmissionFilter[0] << " " << _Tf_transmissionFilter[1] << " " << _Tf_transmissionFilter[2] << "\n";
		o << "\t\tilum " << _illum_illumination << "\n";
		o << "\t\td " << _d_dissolve << "\n";
		o << "\t\tNs " << _NS_specularExponent << "\n";
		o << "\t\tsharpness " << _sharpness_sharpness << "\n";
		o << "\t\tNi " << _Ni_opticalDensity << "\n";
		o << "\treflection map statement :\n";
		o << "\ttodo\n";
		return o;
	}

	const string& Material::getName() const
	{
		return _name;
	}

	const vec3& Material::getAmbient() const
	{
		return _Ka_ambient;
	}

	const vec3& Material::getDiffuse() const
	{
		return _Kd_diffuse;
	}

	const vec3& Material::getSpecular() const
	{
		return _Ks_specular;
	}

	const vec3& Material::getTransmissionFilter() const
	{
		return _Tf_transmissionFilter;
	}

	int Material::getIllumination() const
	{
		return _illum_illumination;
	}

	float Material::getDissolve() const
	{
		return _d_dissolve;
	}

	bool Material::getHalo() const
	{
		return _halo;
	}

	float Material::getSpecularExponent() const
	{
		return _NS_specularExponent;
	}

	float Material::getSharpness() const
	{
		return _sharpness_sharpness;
	}

	float Material::getopticalDensity() const
	{
		return _Ni_opticalDensity;
	}


	Map* Material::getKamap() const
	{
		return _Ka_map;
	}

	Map* Material::getKdmap() const
	{
		return _Kd_map;
	}

	Map* Material::getKsmap() const
	{
		return _Ks_map;
	}

	Map* Material::getNsmap() const
	{
		return _Ns_map;
	}

	Map* Material::getdmap() const
	{
		return _d_map;
	}

	Map* Material::getDispmap() const
	{
		return _disp_map;
	}

	Map* Material::getDecalmap() const
	{
		return _decal_map;
	}

	Map* Material::getBumpmap() const
	{
		return _bump_map;
	}

	void Material::setAmbient(const vec3& ka)
	{
		_Ka_ambient = ka;
	}

	void Material::setDiffuse(const vec3& kd)
	{
		_Kd_diffuse = kd;
	}

	void Material::setSpecular(const vec3& ks)
	{
		_Ks_specular = ks;
	}

	void Material::setTransmissionFilter(const vec3& tf)
	{
		_Tf_transmissionFilter = tf;
	}

	void Material::setIllumination(int illum)
	{
		_illum_illumination = illum;
	}

	void Material::setDissolve(float d)
	{
		_d_dissolve = d;
	}

	void Material::setHalo(bool h)
	{
		_halo = h;
	}

	void Material::setSpecularExponent(float ns)
	{
		_NS_specularExponent = ns;
	}

	void Material::setSharpness(float sharp)
	{
		_sharpness_sharpness = sharp;
	}

	void Material::setopticalDensity(float ni)
	{
		_Ni_opticalDensity = ni;
	}

	void Material::setEmissiveCoeficient(const vec3& ke)
	{
		_Ke = ke;
	}


	void Material::setKamap(const string& path) throw(...)
	{
		if (_Ka_map)delete _Ka_map;
		try {
			_Ka_map = new Map(mapType::Ka, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setKamap(const string& path) throw(...)] " + e.what());
		}
	}

	void Material::setKdmap(const string& path) throw(...)
	{
		if (_Kd_map)delete _Kd_map;
		try {
			_Kd_map = new Map(mapType::Kd, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setKdmap(const string& path) throw(...)] " + e.what());
		}
	}

	void Material::setKsmap(const string& path) throw(...)
	{
		if (_Ks_map)delete _Ks_map;
		try {
			_Ks_map = new Map(mapType::Ks, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setKsmap(const string& path) throw(...)] " + e.what());
		}
	}

	void Material::setNsmap(const string& path) throw(...)
	{
		if (_Ns_map)delete _Ns_map;
		try {
			_Ns_map = new Map(mapType::Ns, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setNsmap(const string& path) throw(...)] " + e.what());
		}
	}

	void Material::setdmap(const string& path) throw(...)
	{
		if (_d_map)delete _d_map;
		try {
			_d_map = new Map(mapType::d, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setdmap(const string& path) throw(...)] " + e.what());
		}
	}

	void Material::setDispmap(const string& path) throw(...)
	{
		if (_disp_map)delete _disp_map;
		try {
			_disp_map = new Map(mapType::disp, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setDispmap(const string& path) throw(...)] " + e.what());
		}
	}

	void Material::setDecalmap(const string& path) throw(...)
	{
		if (_decal_map)delete _decal_map;
		try {
			_decal_map = new Map(mapType::decal, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setDecalmap(const string& path) throw(...)] " + e.what());
		}
	}

	void Material::setBumpmap(const string& path) throw(...)
	{
		if (_bump_map)delete _bump_map;
		try {
			_bump_map = new Map(mapType::bump, path);
		}
		catch (exception e) {
			throw invalid_argument("[Material " + _name + "] [setBumpmap(const string& path) throw(...)] " + e.what());
		}
	}


	ostream& operator<<(ostream& o, const Material& m)
	{
		m.print(o);
		return o;
	}

}
