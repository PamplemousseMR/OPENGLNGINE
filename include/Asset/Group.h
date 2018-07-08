#pragma once
#include<string>
#include<vector>
#include<glm/glm.hpp>
#include<iostream>

namespace Component
{
	class Mesh;
}

namespace Assets
{
	class Material;

	class Group
	{

		private :

			std::string _name;
			std::vector<Component::Mesh*> _meshs;
			std::vector<Material*> _materials;

		public:

			Group(const std::string&);
			~Group();

			void add(const std::vector<glm::vec3>&, const std::vector<glm::vec3>*, const std::vector<glm::vec2>*, const std::vector<glm::vec3>&, const std::string*) throw(...);

			const std::string& getName() const;
			const std::vector<Component::Mesh*>& getMeshs() const;
			Material* getLastMaterial() const;
			const std::vector<Material*>& getMaterials() const;

			std::ostream& print(std::ostream& o) const;
	};

	std::ostream& operator<<(std::ostream& o, const Group& m);

}
