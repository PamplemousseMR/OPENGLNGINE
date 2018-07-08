#include "Asset/Object.h"
#include "Asset/Group.h"

using namespace std;

namespace Assets
{

	Object::Object(const string& name)
		: m_name(name)
	{
#ifdef _DEBUG
        cout << "[Object " << m_name << "] [Object(const string& name)]..." << endl;
        cout << "[Object " << m_name << "] [Object(const string& name)]...\tsuccess" << endl;
#endif
	}

	ostream& Object::print(ostream& o) const
	{
		o << "[Object " << m_name << "]" << endl;
		for (Group* g : m_groups)
			cout << "\t" << *g << "\n";
		return o;
	}

	Object::~Object()
	{
#ifdef _DEBUG
        cout << "[Object " << m_name << "] [~Object()]..." << endl;
#endif
		for (Group* m : m_groups)
			if (m) delete m;
#ifdef _DEBUG
        cout << "[Object " << m_name << "] [~Object()]...\tsuccess"<<endl;
#endif
	}

	const vector<Group*>& Object::getGroups() const
	{
		return m_groups;
	}

	const string& Object::getName() const
	{
		return m_name;
	}

	Group* Object::getLastGroup() const
	{
		return m_groups.back();
	}

	void Object::addGroup(const string& name)
	{
		m_groups.push_back(new Group(name));
	}

	ostream& operator<<(ostream& o, const Object& m)
	{
		m.print(o);
		return o;
	}

}
