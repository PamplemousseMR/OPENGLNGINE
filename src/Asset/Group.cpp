#include "Asset/Group.hpp"
#include "Component/Mesh.hpp"
#include "Asset/Material.hpp"

using namespace std;
using namespace glm;
using namespace Component;

namespace Assets
{

	Group::Group(const string& name)
		: m_name(name)
	{
#ifdef _DEBUG
        cout << "[Group " << m_name << "] [Group(const string& name)]..." << endl;
        cout << "[Group " << m_name << "] [Group(const string& name)]...\tsucess" << endl;
#endif
	}

	Group::~Group()
	{
#ifdef _DEBUG
        cout << "[Group " << m_name << "] [~Group()]...";
#endif
		for (Mesh* m : m_meshs)
			if (m) delete m;
		for (Material* m : m_materials)
			if (m) delete m;
#ifdef _DEBUG
        cout << "[Group " << m_name << "] [~Group()]...\tsuccess" << endl;
#endif
	}

	void Group::add(const vector<vec3>& vertex, const vector<vec3>* normal, const vector<vec2>* textCoord, const vector<vec3>& index, const string* name) throw()
	{
		if (name)
			m_materials.push_back(new Material(*name));
		else
			m_materials.push_back(new Material(m_name));

		m_meshs.push_back(new Mesh(name ? *name : m_name));
		Mesh* mesh = m_meshs.back();
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
			throw invalid_argument("[Group " + m_name  + "] [add(const vector<vec3>& vertex, const vector<vec3>* normal, const vector<vec2>* textCoord, const vector<vec3>& index, const string* name) throw()] " + e.what());
		}
	}

	const string& Group::getName() const
	{
		return m_name;
	}

	const vector<Mesh*>& Group::getMeshs() const
	{
		return m_meshs;
	}

	Material* Group::getLastMaterial() const
	{
		return m_materials.back();
	}

	const vector<Material*>& Group::getMaterials() const
	{
		return m_materials;
	}

	ostream& Group::print(ostream& o) const
	{
		o << "[Group " << m_name << "]\n";
		for (int i(0); i < m_meshs.size(); i++)
		{
			if (i > 0)
				o << "\n";
			string mat = m_materials[i]->getName();
			o << "\t\t mesh : " << m_meshs[i]->getName() << " [normal->" << m_meshs[i]->hasNormal() << " textCoord->" << m_meshs[i]->hasTextureCoord() << "] , material : " << mat;
		}
		return o;
	}

	ostream& operator<<(ostream& o, const Group& m)
	{
		m.print(o);
		return o;
	}

}
