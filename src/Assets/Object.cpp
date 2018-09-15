#include "Assets/Object.hpp"
#include "Assets/Group.hpp"

using namespace std;

namespace Assets
{

    Object::Object(const string& _name) noexcept :
        m_name(_name)
    {
    }

    ostream& Object::print(ostream& _o) const noexcept
    {
        _o << "[Object " << m_name << "]" << endl;
        for (Group* g : m_groups)
        {
            cout << "\t" << *g << "\n";
        }
        return _o;
    }

    Object::~Object() noexcept
    {
        for (Group* m : m_groups)
        {
            delete m;
        }
    }

    const vector<Group*>& Object::getGroups() const noexcept
    {
        return m_groups;
    }

    Group* Object::getLastGroup() const noexcept
    {
        return m_groups.back();
    }

    void Object::addGroup(const string& _name) noexcept
    {
        m_groups.push_back(new Group(_name));
    }

    ostream& operator<<(ostream& _o, const Object& _m) noexcept
    {
        _m.print(_o);
        return _o;
    }

}
