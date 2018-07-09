#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace Component
{
	class Mesh;
}

namespace Assets
{
class Material;

class Group
{

public:

    Group(const std::string&);
    ~Group();

	void add(const std::vector<glm::vec3>&, const std::vector<glm::vec3>*, const std::vector<glm::vec2>*, const std::vector<glm::vec3>&, const std::string*) throw();

    const std::string& getName() const;
    const std::vector<Component::Mesh*>& getMeshs() const;
    Material* getLastMaterial() const;
    const std::vector<Material*>& getMaterials() const;

    std::ostream& print(std::ostream& o) const;

private :

    std::string m_name;
    std::vector<Component::Mesh*> m_meshs;
    std::vector<Material*> m_materials;

};

std::ostream& operator<<(std::ostream& o, const Group& m);

}
