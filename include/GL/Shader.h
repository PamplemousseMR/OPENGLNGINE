#pragma once
#include <GL\glew.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace GL {

	enum shaderType
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER
	};

	class Shader
	{

	private:

		GLuint _id;
		shaderType _type;
		std::string _sources;

	public:

		Shader(shaderType);
		~Shader();
		Shader(const Shader&);
		Shader& operator=(const Shader&);

		void compile() const throw(...);

		GLenum getType() const;
		GLuint getId() const;

		void setSource(const std::string&);
		void setSourceFromFile(const std::string&) throw(...);
	};

}
