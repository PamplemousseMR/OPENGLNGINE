#include "Asset/Group.hpp"
#include "Component/Mesh.hpp"
#include "Asset/Material.hpp"

using namespace std;
using namespace glm;
using namespace Component;

namespace Assets
{

    Group::Group(const string& _name) noexcept :
        m_name(_name)
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

    void Group::add(const vector<vec3>& _vertex, const vector<vec3>* _normal, const vector<vec2>* _textCoord, const vector<vec3>& _index, const string* _name)
    {
        m_materials.push_back(new Material(_name ? *_name : m_name));
        m_meshs.push_back(new Mesh(_name ? *_name : m_name));
        Mesh* mesh = m_meshs.back();
        try {
            if(_normal && _textCoord)
            {
                mesh->loadMesh(_vertex, *_normal, *_textCoord, _index);
            }
            else if(_normal)
            {
                mesh->loadMesh(_vertex, *_normal, _index);
            }
            else if(_textCoord)
            {
                mesh->loadMesh(_vertex, *_textCoord, _index);
            }
            else
            {
                mesh->loadMesh(_vertex, _index);
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

    ostream& Group::print(ostream& _o) const noexcept
    {
        _o << "[Group " << m_name << "]\n";
        for (int i(0); i < m_meshs.size(); i++)
        {
            if (i > 0)
            {
                _o << "\n";
            }
            string mat = m_materials[i]->getName();
            _o << "\t\t mesh : " << m_meshs[i]->getName() << " [normal->" << m_meshs[i]->hasNormal() << " textCoord->" << m_meshs[i]->hasTextureCoord() << "] , material : " << mat;
        }
        return _o;
    }

    ostream& operator<<(ostream& _o, const Group& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }

}
