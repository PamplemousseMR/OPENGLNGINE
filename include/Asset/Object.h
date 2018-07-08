#pragma once
#include<string>
#include<vector>
#include<iostream>

namespace Assets
{
	class Group;
	class Object
	{

		private:

			std::string _name;
			std::vector<Group*> _groups;

		public:

			Object(const std::string&);
			~Object();

			void addGroup(const std::string&);

			const std::vector<Group*>& getGroups() const;
			Group* getLastGroup() const;
			const std::string& getName() const;

			std::ostream& print(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream&, const Object&);

}

