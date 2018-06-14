#include "Group.h"
#include"Mesh.h"
#include"Material.h"

using namespace std;
using namespace glm;
using namespace Component;

namespace Assets
{

	Group::Group(const string& name)
		: _name(name)
	{
#ifdef _DEBUG
		cout << "[Group " << _name << "] [Group(const string& name)]..." << endl;
		cout << "[Group " << _name << "] [Group(const string& name)]...\tsucess" << endl;
#endif
	}

	Group::~Group()
	{
#ifdef _DEBUG
		cout << "[Group " << _name << "] [~Group()]...";
#endif
		for (Mesh* m : _meshs)
			if (m) delete m;
		for (Material* m : _materials)
			if (m) delete m;
#ifdef _DEBUG
		cout << "[Group " << _name << "] [~Group()]...\tsuccess" << endl;
#endif
	}

	void Group::add(const vector<vec3>& vertex, const vector<vec3>* normal, const vector<vec2>* textCoord, const vector<vec3>& index, const string* name) throw(...)
	{
		if (name)
			_materials.push_back(new Material(*name));
		else
			_materials.push_back(new Material(_name));

		_meshs.push_back(new Mesh(name ? *name : _name));
		Mesh* mesh = _meshs.back();
		try {
			if (normal && textCoord)
				mesh->loadMesh(vertex, *normal, *textCoord, index);
			else if (normal)
				mesh->loadMesh(vertex, *normal, index);
			else if (textCoord)
				mesh->loadMesh(vertex, *textCoord, index);
			else
				mesh->loadMesh(vertex, index);
		}
		catch (invalid_argument e){
			throw invalid_argument("[Group " + _name  + "] [add(const vector<vec3>& vertex, const vector<vec3>* normal, const vector<vec2>* textCoord, const vector<vec3>& index, const string* name) throw(...)] " + e.what());
		}
	}

	const string& Group::getName() const
	{
		return _name;
	}

	const vector<Mesh*>& Group::getMeshs() const
	{
		return _meshs;
	}

	Material* Group::getLastMaterial() const
	{
		return _materials.back();
	}

	const vector<Material*>& Group::getMaterials() const
	{
		return _materials;
	}

	ostream& Group::print(ostream& o) const
	{
		o << "[Group " << _name << "]\n";
		for (int i(0); i < _meshs.size(); i++)
		{
			if (i > 0)
				o << "\n";
			string mat = _materials[i]->getName();
			o << "\t\t mesh : " << _meshs[i]->getName() << " [normal->" << _meshs[i]->hasNormal() << " textCoord->" << _meshs[i]->hasTextureCoord() << "] , material : " << mat;
		}
		return o;
	}

	ostream& operator<<(ostream& o, const Group& m)
	{
		m.print(o);
		return o;
	}

}
