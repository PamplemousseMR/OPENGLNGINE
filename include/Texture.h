#pragma once
#include <GL\glew.h>
#include <vector>
#include <iostream>
#include <SOIL\SOIL.h>
#include <string>

namespace GL
{

	enum textureType
	{
		TEXTURE_1D = GL_TEXTURE_1D,
		TEXTURE_2D = GL_TEXTURE_2D,
	};

	class Texture
	{

	private:

		static std::vector<bool> s_location;
		static bool s_first;
		textureType _type;
		std::string _name;
		bool _hasAlpha;
		GLuint _id;
		int _location;

	public:

		Texture(textureType);
		~Texture();

		int load(const char*) throw(...);
		void generateMipmap() const;
		void bind() throw(...);
		void unbind();

		GLuint getId() const;
		int getLocation() const;
		textureType getType() const;
		const std::string& getName() const;

		void setParameter(GLenum, GLint) const;

	};

}

