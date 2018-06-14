#pragma once
#include <GL/glew.h>
#include <iostream>

namespace GL 
{
	enum bufferType
	{
		VAO,
		VBO,
		EBO
	};

	class Buffer
	{

	private:

		GLuint _id;
		bufferType _type;

	public:

		Buffer(bufferType);
		~Buffer();
		Buffer(const Buffer&) throw(...);
		Buffer& operator=(const Buffer&) throw(...);

		void bind() const;
		void unbind() const;

		bufferType type() const;
		GLuint getId() const;

	};

}

