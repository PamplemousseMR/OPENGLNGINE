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

    Object(const std::string&);
    ~Object();
    Object(const Object&);
    Object(Object&&);
    Object& operator=(const Object&);
    Object& operator=(Object&&);

    void addGroup(const std::string&);

    const std::vector<Group*>& getGroups() const;
    Group* getLastGroup() const;
    inline const std::string& getName() const;

    std::ostream& print(std::ostream&) const;

private:

    std::string m_name {};
    std::vector<Group*> m_groups {};

};

std::ostream& operator<<(std::ostream&, const Object&);

inline const std::string& Object::getName() const
{
    return m_name;
}

}

