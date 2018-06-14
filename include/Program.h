#pragma once
#include<vector>
#include<GL/glew.h>
#include<iostream>

namespace GL {

	class Shader;

	class Program
	{

	private:

		GLuint _id;
		bool _toggled;
		std::vector<Shader*> _shaders;

	public:

		Program();
		~Program();

		void attach(Shader* shader);
		void detach(Shader* shader);
		void detachAll();
		void link() const throw(...);
		void toggle();

		bool isActive() const;
		GLuint getId() const;

	};

}