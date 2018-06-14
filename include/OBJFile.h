#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<glm\glm.hpp>
#include <chrono>

namespace Assets
{
	class Material;
	class Object;
	class OBJFile
	{

		private:


			std::vector<Object*> _objects;
			std::string _name;
			long long _loadTime;

			std::vector<std::string> split(const std::string & str, char splitter) const;
			std::vector<std::string> removenullptr(const std::vector<std::string> & str) const;
			void push(std::vector<glm::vec3>*, std::vector<glm::vec3>*, std::vector<glm::vec2>*, std::vector<glm::vec3>*, std::string*) const throw(...);
			std::vector<Material*> findMaterial(const std::string&) const;
			void loadMTLFile(const std::string&) const throw(...);

		public:

			OBJFile();
			~OBJFile();

			void load(const std::string&) throw(...);

			const std::vector<Object*>& getObjects() const;
			long long getLoadTime() const;

			std::ostream& print(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream& o, const OBJFile&);

}

