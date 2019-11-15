#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

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
    Group(const Group&);
    Group(Group&&);
    Group& operator=(const Group&);
    Group& operator=(Group&&);

    void add(const std::vector<glm::vec3>&, const std::vector<glm::vec3>*, const std::vector<glm::vec2>*, const std::vector<glm::vec3>&, const std::string*);

    inline const std::string& getName() const;
    const std::vector<Component::Mesh*>& getMeshs() const;

    std::ostream& print(std::ostream& o) const;

private :

    std::string m_name {};
    std::vector<Component::Mesh*> m_meshs {};

};

std::ostream& operator<<(std::ostream& o, const Group& m);

inline const std::string& Group::getName() const
{
    return m_name;
}

}
