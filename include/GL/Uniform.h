#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>

namespace GL {

	class Uniform
	{

	private:

		GLuint _location;
		std::string _name;

	public:

		Uniform(const std::string &, GLuint);
		~Uniform();
		void operator= (bool);
		void operator= (int);
		void operator= (float);
		void operator= (const glm::vec2&);
		void operator= (const glm::vec3&);
		void operator= (const glm::vec4&);
		void operator= (const glm::mat4&);
		void operator= (const glm::mat3&);

		GLuint getLocation() const;
		const std::string& getName() const;

	};

}