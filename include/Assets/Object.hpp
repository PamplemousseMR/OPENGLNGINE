#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace Assets
{
class Group;

class Object
{

public:

    Object(const std::string&) noexcept;
    ~Object() noexcept;
    Object(const Object&);
    Object(Object&&);
    Object& operator=(const Object&);
    Object& operator=(Object&&);

    void addGroup(const std::string&) noexcept;

    const std::vector<Group*>& getGroups() const noexcept;
    Group* getLastGroup() const noexcept;
    inline const std::string& getName() const noexcept;

    std::ostream& print(std::ostream&) const noexcept;

private:

    std::string m_name {};
    std::vector<Group*> m_groups {};

};

std::ostream& operator<<(std::ostream&, const Object&) noexcept;

inline const std::string& Object::getName() const noexcept
{
    return m_name;
}

}

