#pragma once

#include <glm/vec3.hpp>

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

    Group(const std::string&) noexcept;
    ~Group() noexcept;

    void add(const std::vector<glm::vec3>&, const std::vector<glm::vec3>*, const std::vector<glm::vec2>*, const std::vector<glm::vec3>&, const std::string*);

    inline const std::string& getName() const noexcept;
    const std::vector<Component::Mesh*>& getMeshs() const noexcept;
    Material* getLastMaterial() const noexcept;

    std::ostream& print(std::ostream& o) const noexcept;

private :

    std::string m_name {};
    std::vector<Component::Mesh*> m_meshs {};

};

std::ostream& operator<<(std::ostream& o, const Group& m) noexcept;

inline const std::string& Group::getName() const noexcept
{
    return m_name;
}

}
