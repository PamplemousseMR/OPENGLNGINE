#include "Asset/Group.hpp"
#include "Component/Mesh.hpp"
#include "Asset/Material.hpp"

using namespace std;
using namespace glm;
using namespace Component;

namespace Assets
{

    Group::Group(const string& name) noexcept :
        m_name(name)
    {
    }

    Group::~Group()
    {
        for (Mesh* m : m_meshs)
        {
            delete m;
        }
        for (Material* m : m_materials)
        {
            delete m;
        }
    }

    void Group::add(const vector<vec3>& vertex, const vector<vec3>* normal, const vector<vec2>* textCoord, const vector<vec3>& index, const string* name)
    {
        m_materials.push_back(new Material(name ? *name : m_name));
        m_meshs.push_back(new Mesh(name ? *name : m_name));
        Mesh* mesh = m_meshs.back();
        try {
            if (normal && textCoord)
            {
                mesh->loadMesh(vertex, *normal, *textCoord, index);
            }
            else if (normal)
            {
                mesh->loadMesh(vertex, *normal, index);
            }
            else if (textCoord)
            {
                mesh->loadMesh(vertex, *textCoord, index);
            }
            else
            {
                mesh->loadMesh(vertex, index);
            }
        }
        catch (const invalid_argument& e)
        {
            throw invalid_argument("[Group] " + string(e.what()));
        }
    }

    const string& Group::getName() const noexcept
    {
        return m_name;
    }

    const vector<Mesh*>& Group::getMeshs() const noexcept
    {
        return m_meshs;
    }

    Material* Group::getLastMaterial() const noexcept
    {
        return m_materials.back();
    }

    const vector<Material*>& Group::getMaterials() const noexcept
    {
        return m_materials;
    }

    ostream& Group::print(ostream& o) const noexcept
    {
        o << "[Group " << m_name << "]\n";
        for (int i(0); i < m_meshs.size(); i++)
        {
            if (i > 0)
            {
                o << "\n";
            }
            string mat = m_materials[i]->getName();
            o << "\t\t mesh : " << m_meshs[i]->getName() << " [normal->" << m_meshs[i]->hasNormal() << " textCoord->" << m_meshs[i]->hasTextureCoord() << "] , material : " << mat;
        }
        return o;
    }

    ostream& operator<<(ostream& o, const Group& m) noexcept
    {
        m.print(o);
        return o;
    }

}
