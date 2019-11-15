#include "Assets/Object.hpp"
#include "Assets/Group.hpp"

using namespace std;

namespace Assets
{

    Object::Object(const string& _name) :
        m_name(_name)
    {
    }

    ostream& Object::print(ostream& _o) const
    {
        _o << "[Object " << m_name << "]" << endl;
        for(Group* g : m_groups)
        {
            cout << "\t" << *g << "\n";
        }
        return _o;
    }

    Object::~Object()
    {
        for(Group* g : m_groups)
        {
            delete g;
        }
    }

    Object::Object(const Object& _obj) :
        m_name(_obj.m_name)
    {
        for(Group* g : _obj.m_groups)
        {
            m_groups.push_back(new Group(*g));
        }
    }

    Object::Object(Object&& _obj) :
        m_name(move(_obj.m_name))
    {
        for(size_t i=0 ; i<_obj.m_groups.size() ; ++i)
        {
            m_groups.push_back(_obj.m_groups[i]);
            _obj.m_groups[i] = nullptr;
        }
    }

    Object& Object::operator=(const Object& _obj)
    {
        if(this != &_obj)
        {
            for(Group* g : m_groups)
            {
                delete g;
            }
            m_groups.clear();
            m_name = _obj.m_name;
            for(Group* g : _obj.m_groups)
            {
                m_groups.push_back(new Group(*g));
            }
        }
        return *this;
    }

    Object& Object::operator=(Object&& _obj)
    {
        if(this != &_obj)
        {
            for(Group* g : m_groups)
            {
                delete g;
            }
            m_groups.clear();
            m_name = move(_obj.m_name);
            for(size_t i=0 ; i<_obj.m_groups.size() ; ++i)
            {
                m_groups.push_back(_obj.m_groups[i]);
                _obj.m_groups[i] = nullptr;
            }
        }
        return *this;
    }

    const vector<Group*>& Object::getGroups() const
    {
        return m_groups;
    }

    Group* Object::getLastGroup() const
    {
        return m_groups.back();
    }

    void Object::addGroup(const string& _name)
    {
        m_groups.push_back(new Group(_name));
    }

    ostream& operator<<(ostream& _o, const Object& _m)
    {
        _m.print(_o);
        return _o;
    }

}
