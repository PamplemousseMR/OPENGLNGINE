#include "Asset/Object.h"
#include "Asset/Group.h"

using namespace std;

namespace Assets
{

	Object::Object(const string& name)
		: _name(name)
	{
#ifdef _DEBUG
		cout << "[Object " << _name << "] [Object(const string& name)]..." << endl;
		cout << "[Object " << _name << "] [Object(const string& name)]...\tsuccess" << endl;
#endif
	}

	ostream& Object::print(ostream& o) const
	{
		o << "[Object " << _name << "]" << endl;
		for (Group* g : _groups)
			cout << "\t" << *g << "\n";
		return o;
	}

	Object::~Object()
	{
#ifdef _DEBUG
		cout << "[Object " << _name << "] [~Object()]..." << endl;
#endif
		for (Group* m : _groups)
			if (m) delete m;
#ifdef _DEBUG
		cout << "[Object " << _name << "] [~Object()]...\tsuccess"<<endl;
#endif
	}

	const vector<Group*>& Object::getGroups() const
	{
		return _groups;
	}

	const string& Object::getName() const
	{
		return _name;
	}

	Group* Object::getLastGroup() const
	{
		return _groups.back();
	}

	void Object::addGroup(const string& name)
	{
		_groups.push_back(new Group(name));
	}

	ostream& operator<<(ostream& o, const Object& m)
	{
		m.print(o);
		return o;
	}

}
